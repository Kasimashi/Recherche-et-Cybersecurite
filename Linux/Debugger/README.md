# Debugguer et outils relatifs sous linux

Le dernier recours dans les modules de débogage est d’utiliser un débogueur pour parcourir le code, surveiller la valeur des variables et des registres de machines. Cette approche prend beaucoup de temps et devrait être évitée dans la mesure du possible. Néanmoins, la perspective fine sur le code qui est réalisée par un débogueur est parfois inestimable.
L’utilisation d’un débogueur interactif sur le noyau est un défi. Le noyau fonctionne dans son propre espace au nom de tous les processus du système. Par conséquent, un certain nombre de
les capacités communes fournies par les débogueurs de l’espace utilisateur, comme les points d’arrêt et les étapes simples, sont plus difficiles à trouver dans le noyau. Dans cette section, nous examinons plusieurs moyens de déboguer le noyau ; chacun d’eux a des avantages et des inconvénients.

## Utilisation de gdb

gdb peut être très utile pour regarder le système interne. Utilisation compétente du débuguer à ce niveau nécessite une certaine connaissance avec les commandes gdb, une certaine compréhension du code d’assemblage pour la plate-forme cible, et la capacité de faire correspondre le code source et l’assemblage optimisé. Le débogueur doit être invoqué comme si le noyau était une application. En plus de spécifier le nom de fichier pour l’image du noyau ELF, vous devez fournir le nom d’un fichier de base sur la ligne de commande. Pour un noyau en cours d’exécution, ce fichier core est l’image du noyau, /proc/kcore. Une invocation typique de gdb ressemble à ce qui suit :

``gdb /usr/src/linux/vmlinux /proc/kcore``

Le premier argument est le nom de l’exécutable du noyau ELF non compressé, pas zImage ou bzImage ou tout ce qui a été construit spécifiquement pour l’environnement de démarrage.

Le deuxième argument sur la ligne de commande gdb est le nom du fichier core. Comme tout fichier dans /proc, /proc/kcore est généré lorsqu’il est lu. Lorsque l’appel système en lecture s’exécute dans le système de fichiers /proc, il correspond à une fonction de génération de données plutôt qu’à une fonction de récupération de données.
kcore est utilisé pour représenter le noyau « exécutable » dans le format d’un fichier core ; c’est un fichier énorme, car il représente l’espace entier de l’adresse du noyau, qui correspond à toute la mémoire physique. À partir de gdb, vous pouvez regarder les variables du noyau en lançant les commandes standard de gdb. Par exemple, p jiffies affiche le nombre de ticks d’horloge du démarrage du système à l’heure actuelle.

Lorsque vous imprimez des données à partir de gdb, le noyau est toujours en cours d’exécution, et les différents éléments de données ont des valeurs différentes à différents moments ; gdb, cependant, optimise l’accès au fichier de base en cachant les données qui ont déjà été lues. Si vous essayez de regarder la variable jiffies encore une fois, vous obtiendrez la même réponse qu’avant. La mise en cache des valeurs pour éviter l’accès supplémentaire au disque est un comportement correct pour les fichiers de base conventionnels, mais n’est pas pratique lorsqu’une image de base « dynamique » est utilisée.

La solution est de lancer la commande ``core-file/proc/kcore`` à chaque fois que vous voulez vider le cache gdb ; le débogueur se prépare à utiliser un nouveau fichier core et rejette toute information ancienne. Cependant, vous n’aurez pas toujours besoin de créer un fichier core lors de la lecture d’une nouvelle donnée ; gdb lit le noyau en morceaux de quelques kilooctets et ne cache que les morceaux qu’il a déjà référencés.

De nombreuses fonctionnalités normalement fournies par gdb ne sont pas disponibles lorsque vous travaillez avec le noyau. Par exemple, gdb ne peut pas modifier les données du noyau ; il s’attend à ce qu’un programme soit débogué sous son propre contrôle avant de jouer avec son image mémoire. Il n’est pas non plus possible de définir des points d’arrêt ou des watchpoints, ou de passer par les fonctions du noyau en une seule étape.

Notez que, pour avoir des informations sur les symboles disponibles pour gdb, vous devez compiler votre noyau avec l’option CONFIG_DEBUG_INFO. Le résultat est une image du noyau beaucoup plus grande sur le disque, mais, sans cette information, creuser à travers les variables du noyau est presque impossible.

Avec les informations de débogage disponibles, vous pouvez en apprendre beaucoup sur ce qui se passe à l’intérieur du noyau. gdb imprime heureusement des structures, suit des pointeurs, etc. Une chose qui est plus difficile, cependant, est l’examen des modules. Comme les modules ne font pas partie de l’image vmlinux passée à gdb, le débogueur n’en sait rien. Heureusement, depuis le noyau 2.6.7, il est possible d’enseigner à gdb ce qu’il doit savoir pour examiner les modules chargeables.

Les modules chargeables Linux sont des images exécutables au format ELF ; en tant que tels, ils ont été divisés en de nombreuses sections. Un module typique peut contenir une douzaine de sections ou plus, mais il y en a typiquement trois qui sont pertinentes dans une session de débogage :
- .text
Cette section contient le code exécutable du module. Le débogueur doit savoir où cette section doit être capable de donner des tracebacks ou de définir des points d’arrêt. (Aucune de ces opérations n’est pertinente lors de l’exécution du débogueur sur /proc/kcore, mais elles peuvent être utiles lors de l’utilisation de kgdb, décrite ci-dessous).

- .data & .bss
Ces deux sections contiennent les variables du module. Toute variable qui n’est pas initialisée au moment de la compilation finit dans . BSS, tandis que ceux qui sont initialisés vont dans .data.

Faire fonctionner gdb avec des modules chargeables nécessite d’informer le débogueur de l’endroit où les sections d’un module donné ont été chargées. Ces informations sont disponibles dans sysfs, sous ``/sys/module``. Par exemple, après le chargement du module scull, le répertoire */sys/module/scull/sections* contient des fichiers avec des noms tels que . text; le contenu de chaque fichier est l’adresse de base de cette section.

Nous sommes maintenant en mesure d’émettre une commande gdb pour lui parler de notre module. La commande dont nous avons besoin est *add-symbol-file* ; cette commande prend comme paramètres le nom du fichier objet du module, le .text adress et une série de paramètres optionnels qui décrivent où d’autres sections d’intérêt ont été mises. Après avoir fouillé les données de la section du module dans sysfs, nous pouvons construire une commande telle que :

```

(gdb) add-symbol-file .../scull.ko 0xd0832000 \ 
	-s .bss 0xd0837100 \ 
	-s .data 0xd0836be0
```

Nous avons inclus un petit script dans l’exemple source (gdbline) qui peut créer cette commande pour un module donné. Nous pouvons maintenant utiliser gdb pour examiner les variables dans notre module chargeable. Voici un exemple rapide tiré d’une session de débogage de scull :

```

(gdb) add-symbol-file scull.ko 0xd0832000 \
-s .bss 0xd0837100 \
 -s .data 0xd0836be0
add symbol table from file "scull.ko" at
 .text_addr = 0xd0832000
 .bss_addr = 0xd0837100
 .data_addr = 0xd0836be0
(y or n) y
Reading symbols from scull.ko...done.
(gdb) p scull_devices[0]
$1 = {data = 0xcfd66c50,
 quantum = 4000,
 qset = 1000,
 size = 20881,
 access_key = 0,
 ...}

```

Ici, nous voyons que le premier dispositif scull détient actuellement 20.881 octets. Si nous le voulions, nous pourrions suivre la chaîne de données, ou examiner toute autre chose d’intérêt dans le module.
Voici une autre astuce utile qu’il vaut la peine de connaître :

``(gdb) print *(address)``

Ici, remplissez une adresse hexadécimale pour l’adresse ; la sortie est un numéro de fichier et de ligne pour le code correspondant à cette adresse. Cette technique peut être utile, par exemple, pour trouver où un pointeur de fonction pointe vraiment. Nous ne pouvons toujours pas effectuer de tâches de débogage typiques comme définir des points d’arrêt ou modifier des données ; pour effectuer ces opérations, nous devons utiliser un outil comme kdb (décrit ci-dessous) ou kgdb (que nous allons bientôt).

## Kdb Kernel Debugguer

De nombreux lecteurs peuvent se demander pourquoi le noyau n’a pas de fonctionnalités de débogage plus avancées intégrées. La réponse, tout simplement, est que Linus ne croit pas aux débogueurs interactifs. Il craint qu’elles ne conduisent à de mauvaises corrections, celles qui corrigent les symptômes plutôt que d’aborder la véritable cause des problèmes. Ainsi, aucun débogueur intégré.

D’autres développeurs du noyau, cependant, voient une utilisation occasionnelle d’outils de débogage interactifs. Un de ces outils est le débogueur du noyau kdb, disponible en tant que patch non officiel à partir de oss.sgi.com. Pour utiliser kdb, vous devez obtenir le patch (assurez-vous d’obtenir une version qui correspond à votre version du noyau), l’appliquer, et reconstruire et réinstaller le noyau. Notez que, à ce jour, kdb ne fonctionne que sur les systèmes IA-32 (x86) (bien qu’une version pour l’IA-64 ait existé pendant un certain temps dans le noyau principal avant d’être supprimée).

Une fois que vous exécutez un noyau compatible kdb, il y a plusieurs façons d’entrer dans le débogueur. Appuyer sur la touche Pause (ou Break) de la console lance le débogueur. kdb démarre également quand un noyau oops se produit ou quand un point d’arrêt est atteint. Dans tous les cas, vous voyez un message qui ressemble à ceci :

``

Entering kdb (0xc0347b80) on processor 0 due to Keyboard Entry
[0]kdb>

``

Notez que tout ce que fait le noyau s’arrête lorsque kdb est en cours d’exécution. Rien d’autre ne devrait être exécuté sur un système où vous invoquez kdb ; en particulier, vous ne devriez pas avoir le réseau allumé — sauf, bien sûr, si vous déboguez un pilote réseau. C’est généralement une bonne idée de démarrer le système en mode mono-utilisateur si vous utilisez kdb.

Par exemple, envisagez une session de débogage rapide. En supposant que le pilote est déjà chargé, nous pouvons dire à kdb de définir un point d’arrêt dans scull_read comme suit :
```

[0]kdb> bp scull_read
Instruction(i) BP #0 at 0xcd087c5dc (scull_read)
 is enabled globally adjust 1
[0]kdb> go

```

La commande bp indique à kdb d’arrêter la prochaine fois que le noyau entre dans scull_read. Vous tapez ensuite go pour continuer l’exécution. Après avoir mis quelque chose dans l’un des sculldevices, nous pouvons essayer de le lire en exécutant cat sous un shell sur un autre terminal, donnant ce qui suit :

```

Instruction(i) breakpoint #0 at 0xd087c5dc (adjusted)
0xd087c5dc scull_read: int3
Entering kdb (current=0xcf09f890, pid 1575) on processor 0 due to
Breakpoint @ 0xd087c5dc
[0]kdb>

```

Nous sommes maintenant positionnés au début de scull_read. Pour voir comment nous y sommes arrivés, nous pouvons obtenir une trace de pile :

```

[0]kdb> bt
 ESP EIP Function (args)
0xcdbddf74 0xd087c5dc [scull]scull_read
0xcdbddf78 0xc0150718 vfs_read+0xb8
0xcdbddfa4 0xc01509c2 sys_read+0x42
0xcdbddfc4 0xc0103fcf syscall_call+0x7
[0]kdb>

```

kdb tente d’imprimer les arguments à chaque fonction de la trace d’appel. Cependant, il est confus par les astuces d’optimisation utilisées par le compilateur. Par conséquent, il ne parvient pas à imprimer les arguments à scull_read.

Il est temps d'observer les données. La commande mds manipule les données ; nous pouvons interroger la valeur du pointeur scull_devices avec une commande telle que :
```
[0]kdb> mds scull_devices 1
0xd0880de8 cf36ac00 ....

```

Ici, nous avons demandé un mot (4 octets) de données à partir de l’emplacement de scull_devices; la réponse nous dit que notre tableau de périphériques est à l’adresse 0xd0880de8; la première structure de périphériques elle-même est à 0xcf36ac00. Pour examiner la structure de cet appareil, nous devons utiliser cette adresse :


```

[0]kdb> mds cf36ac00
0xcf36ac00 ce137dbc ....
0xcf36ac04 00000fa0 ....
0xcf36ac08 000003e8 ....
0xcf36ac0c 0000009b ....
0xcf36ac10 00000000 ....
0xcf36ac14 00000001 ....
0xcf36ac18 00000000 ....
0xcf36ac1c 00000001 ....

```

Les huit lignes correspondent ici à la partie initiale de la structure scull_dev. Par conséquent, nous voyons que la mémoire du premier périphérique est allouée à 0xce137dbc, le quantum est 4000 (hex fa0), la taille de l’ensemble quantique est 1000 (hex 3e8), et il y a actuellement 155 (hex 9b) octets stockés dans le périphérique. kdb peut changer les données aussi bien. Supposons que nous voulions couper certaines des données à partir de l’appareil :

```

[0]kdb> mm cf26ac0c 0x50
0xcf26ac0c = 0x50

```

Une commande *cat* va maintenant renvoyer moins de données qu’avant. kdb a un certain nombre d’autres capacités, y compris un seul pas (par des instructions, pas des lignes de code source C), la configuration des points d’arrêt sur l’accès aux données, le désassemblage du code, le passage à travers les listes liées, l’accès aux données du registre, et plus encore. Après avoir appliqué le patch kdb, un ensemble complet de pages de manuel se trouve dans le répertoire Documentation/kdb dans l’arborescence des sources de votre noyau.

## Les Patches kgdb
Les deux approches de débogage interactives que nous avons étudiées jusqu’à présent (utilisant gdb sur /proc/kcore et kdb) ne correspondent pas au type d’environnement auquel les développeurs d’applications utilisateur-espace se sont habitués. Ne serait-ce pas bien s’il y avait un vrai débogueur pour le noyau qui supportait des fonctionnalités comme les variables changeantes, les points d’arrêt, etc.?

Il s’avère qu’une telle solution existe. Il y a, à ce jour, deux correctifs distincts en circulation qui permettent à gdb, avec toutes les capacités, d’être exécuté contre le noyau. Confusément, ces deux patchs sont appelés kgdb. Ils fonctionnent en séparant le système exécutant le noyau de test du système exécutant le débogueur ; les deux sont généralement connectés via un câble série. Par conséquent, le développeur peut exécuter gdb sur son système de bureau stable, tout en fonctionnant sur un noyau tournant sur une boîte de test sacrificielle. La mise en place de gdb dans ce mode prend un peu de temps au départ, mais cet investissement peut être rentable rapidement lorsqu’un bug difficile apparaît.

Ces patchs sont dans un fort état de flux, et peuvent même être fusionnés à un moment donné, de sorte que nous évitons de dire beaucoup au sujet d’eux au-delà où ils sont et leurs caractéristiques de base. Les lecteurs intéressés sont encouragés à regarder et à voir l’état actuel des choses.

Le premier patch kgdb se trouve actuellement dans l’arborescence même du noyau, la zone de transition pour les patchs qui se dirigent vers la ligne principale 2.6. Cette version du patch prend en charge les architectures x86, SuperH, ia64, x86_64, SPARC et PPC 32 bits. En plus du mode de fonctionnement habituel sur un port série, cette version de kgdb peut également communiquer sur un réseau local. Il s’agit simplement d’activer le mode Ethernet et de démarrer avec le paramètre kgdboe défini pour indiquer l’adresse IP à partir de laquelle les commandes de débogage peuvent provenir. La documentation sous Documentation/i386/kgdb décrit comment configurer les choses.

Comme alternative, vous pouvez utiliser le patch kgdb trouvé sur http://kgdb.sf.net/. Cette version du débogueur ne supporte pas le mode de communication réseau (bien qu’il soit dit qu’il soit en cours de développement), mais il a un support intégré pour travailler avec des modules chargeables. Il prend en charge les architectures x86, x86_64, PowerPC et S/390.





