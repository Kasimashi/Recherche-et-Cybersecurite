# Informations utiles sur Linux 

## Arborescence

- bin : contient des programmes (exécutables) susceptibles d'être utilisés par tous les utilisateurs de la machine.

- boot : fichiers permettant le démarrage de Linux.

dev : fichiers contenant les périphériques. En fait – on en reparlera plus tard – ce dossier contient des sous-dossiers qui « représentent » chacun un périphérique. On y retrouve ainsi par exemple le fichier qui représente le lecteur CD.

- etc : fichiers de configuration.

- home : répertoires personnels des utilisateurs. On en a déjà parlé un peu avant : c'est dans ce dossier que vous placerez vos fichiers personnels, à la manière du dossierMes documentsde Windows.

Chaque utilisateur de l'ordinateur possède son dossier personnel. Par exemple, dans mon cas mon dossier personnel se trouve dans/home/mateo21/. S'il y avait un autre utilisateur (appelons-le Patrick) sur mon ordinateur, il aurait eu droit lui aussi à son propre dossier :/home/patrick/.

- lib : dossier contenant les bibliothèques partagées (généralement des fichiers.so) utilisées par les programmes. C'est en fait là qu'on trouve l'équivalent des.dllde Windows.

- media : lorsqu'un périphérique amovible (comme une carte mémoire SD ou une clé USB) est inséré dans votre ordinateur, Linux vous permet d'y accéder à partir d'un sous-dossier demedia. On parle de montage.

- mnt : c'est un peu pareil quemedia, mais pour un usage plus temporaire.

- opt : répertoire utilisé pour les add-ons de programmes.

- proc : contient des informations système.

- root : c'est le dossier personnel de l'utilisateur « root ». Normalement, les dossiers personnels sont placés danshome, mais celui de « root » fait exception. En effet, comme je vous l'ai dit dans le chapitre précédent, « root » est le superutilisateur, le « chef » de la machine en quelque sorte. Il a droit à un espace spécial.

- sbin : contient des programmes système importants.

- tmp : dossier temporaire utilisé par les programmes pour stocker des fichiers.

- usr : c'est un des plus gros dossiers, dans lequel vont s'installer la plupart des programmes demandés par l'utilisateur.

- var : ce dossier contient des données « variables », souvent des logs (traces écrites de ce qui s'est passé récemment sur l'ordinateur).

## Raccourci Clavier

- Ctrl + L : efface le contenu de la console. Utile pour faire un peu de ménage quand votre console est encombrée, ou quand votre boss passe derrière vous et que vous n'aimeriez pas qu'il voie ce que vous étiez en train de faire.

À noter qu'il existe aussi une commande, clear, qui fait exactement la même chose.

- Ctrl + D : envoie le message EOF (fin de fichier) à la console. Si vous tapez ce raccourci dans une ligne de commande vide (c'est-à-dire sans avoir écrit un début de commande au préalable), cela fermera la console en cours.

À noter qu'il existe aussi la commande exit qui a le même effet.

- Shift + PgUp : vous permet de « remonter » dans les messages envoyés par la console. En mode graphique, la molette de la souris accomplit aussi très bien cette action.

La touche Page Up est généralement représentée sur votre clavier par une flèche directionnelle Haut barrée de plusieurs petites lignes horizontales.

- Shift + PgDown : pareil, mais pour redescendre.

- Ctrl + A : ramène le curseur au début de la commande. La touche Origine a le même effet (elle est située à côté de la touche Fin et représentée par une flèche pointant en haut à gauche).

- Ctrl + E : ramène le curseur à la fin de la ligne de commandes. La touche Fin a le même effet.

- Ctrl + U : supprime tout ce qui se trouve à gauche du curseur. Si celui-ci est situé à la fin de la ligne, cette dernière sera donc supprimée.

- Ctrl + K : supprime tout ce qui se trouve à droite du curseur. S'il est situé au début de la ligne, celle-ci sera donc totalement supprimée.

- Ctrl + W : supprime le premier mot situé à gauche du curseur. Un « mot » est séparé par des espaces ; on s'en sert en général pour supprimer le paramètre situé à gauche du curseur.

- Ctrl + Y : si vous avez supprimé du texte avec une des commandes Ctrl + U, Ctrl + K ou 
Ctrl + W qu'on vient de voir, alors le raccourci Ctrl + Y « collera » le texte que vous venez de supprimer. C'est donc un peu comme un couper-coller.

- Ctrl + R : rechercher une ancienne commande Linux en l'écrivant

## .bashrc et .profile

Le .profile est lu à chaque nouvelle console dans laquelle vous vous loggez (vous rentrez votre login / mot de passe). C'est le cas des consoles que vous ouvrez avec Ctrl + Alt + F1 à F6(tty1 à tty6).
Le .bashrc est lu lorsque vous ouvrez une console dans laquelle vous ne vous loggez pas. C'est le cas des consoles que vous ouvrez en mode graphique (Terminal sous Unity, Konsole sous KDE).
<img src="https://user.oc-static.com/files/94001_95000/94341.png">

## Flux de redirection

- Au lieu d'afficher le résultat d'une commande dans une console, il est possible de l'enregistrer dans un fichier. Il suffit d'ajouter le symbole > suivi du nom du fichier à la fin de la commande. Par exemple ls > liste_fichiers.txt enregistre la liste des fichiers dans un fichier plutôt que de l'afficher en console.

- Le symbole>> enregistre à la fin du fichier au lieu de l'écraser s'il existe déjà.

- Les symboles 2> et 2>> permettent de rediriger seulement les erreurs dans un fichier. Quant à 2>&1 il redirige les erreurs dans le même fichier que les messages normaux.

- <code><</code> permet de lire des données depuis un fichier et de les envoyer à une commande, tandis que <code><<</code> lit les données depuis le clavier.

- Le symbole | combine des commandes : les données de la commande à sa gauche sont envoyées à la commande à sa droite. Ainsi, du | sort -nr récupère la liste des fichiers avec leur taille et l'envoie à sort pour qu'il la trie.

## Surveiller l'activité du système

- Linux est multi-tâches (plusieurs programmes peuvent tourner en même temps) et multi-utilisateurs (plusieurs utilisateurs peuvent se servir de la même machine en même temps en s'y connectant via Internet).

- w indique quels utilisateurs sont sur la machine, ce qu'ils font et quelques autres statistiques comme la charge de travail de la machine et son uptime.

- ps affiche la liste des processus, c'est-à-dire des programmes qui tournent sur la machine.topest un équivalent qui met à jour automatiquement la liste au fil du temps.

- La combinaison de touches Ctrl + Cpermet d'arrêter une commande en cours d'exécution dans la console afin de pouvoir reprendre la main.

- kill tue un processus, ce qui signifie qu'il lui demande de s'arrêter. Il a besoin du numéro du processus, généralement fourni parpsoutop. Si le processus ne s'arrête pas, on peut utiliser le paramètre-9 qui coupe brutalement le processus (avec risque de perte de données).

- halt commande l'arrêt de l'ordinateur,reboot son redémarrage.

## Commandes courantes :

- grep : est une commande couramment utilisée pour rechercher un mot dans un fichier.

On peut utiliser des expressions régulières, un système complexe mais puissant, pour effectuer des recherches précises. On fait dans ce cas appel à la commandeegrep.

- sort : trie des lignes de texte par ordre alphabétique. Le paramètre-npermet de trier par ordre numérique.

- wc : compte le nombre de lignes, de mots et d'octets dans un fichier.

- uniq : supprime les doublons d'un fichier.
 
- cut : coupe une partie d'un fichier.

## Arrière plan et avant plan

<img src="https://user.oc-static.com/files/141001_142000/141442.png">

Il est possible d'envoyer des programmes en arrière-plan dans la console afin de garder la main pour lancer de nouvelles commandes.

- Pour lancer un processus en arrière-plan, on peut ajouter le symbole & à la fin de la commande. En revanche, lorsque vous fermez la console, le processus est arrêté. Si vous voulez qu'il continue, utilisez plutôt la commande nohup.

- Si vous avez lancé une commande normalement (en avant-plan) mais que celle-ci s'éternise, vous pouvez utiliser le raccourci Ctrl + Z pour la mettre en pause et récupérer la main. Si vous lancez la commande bg ensuite, elle reprendra son exécution en arrière-plan. Vous pourrez la récupérer au premier plan avec fg à tout moment.

- screen est un programme puissant que vous pouvez installer avec apt-get(il n'est pas présent par défaut). Il permet d'ouvrir plusieurs consoles virtuelles au sein d'une seule et même console, et donc d'exécuter facilement plusieurs processus en parallèle.

## Scheduleur

- date permet d'obtenir la date et l'heure mais aussi de modifier celles-ci.

- at retarde l'exécution d'une commande à une heure ultérieure.

On peut exécuter plusieurs commandes d'affilée en les séparant par des points-virgules :touch fichier.txt; rm fichier.txt.

- sleep permet de faire une pause entre deux commandes exécutées d'affilée.

- crontab permet de programmer des commandes pour une exécution régulière. Par exemple : tous les jours à 18 h 30, tous les lundis et mardis à 12 h, tous les 5 du mois, etc. On modifie la programmation avec crontab -e.

## Tricks Linux

Utiliser un nano intelligent (souris et indentation automatique) : nano -miA source.txt
Créer un alias : nano ~/.bashrc
Mettreleclavierenfr : setxkbmap fr

CAT : (mettre des | entre)

cut -d " " -f 1 // Récupérer le premier champs du fichier séparé par " "
sort | uniq -c //Compter le nombre d'occurence.
sort //Trier
grep ... //pour récupérer les lignes avec ceci.
grep ... | grep ... //Pour faire avec 2 recherches.
uniq //Pour afficher qu'une seule occurence.

python -m SimpleHTTPServer <PORT>

Installer sa carte graphique sur sa VM :
sudo apt install -y nvidia-driver nvidia-cuda-toolkit



Enumération dyn. du rep. Desktop : watch -n 2 ls /home/kasi/Desktop/

youtube-dl --extract-audio --audio-format mp3
