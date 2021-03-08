# GNU/Linux ou "Linux"

## Introduction

Il convient ici de différencier distribution, système d'exploitation et noyaux lorsqu'on parle de :
Debian GNU/Linux : 
- Debian est la distribution liée à GNU/Linux.
- GNU/Linux est un système d'exploitation qui peut être utilisé avec des logiciels libres.
- GNU est un outil pour interargir avec le noyau. Ce sont tout les outils pour rendre un PC utilisable.
- Linux c'est le noyau du système.

L'arborescence linux peut parfois être difficile à appréhender mais elle est finalement simple après l'avoir adopté.

## Le Noyau Linux

Disponible à l'addresse : https://github.com/torvalds/linux

### Le rôle du noyau
Le noyau sert d'abord à contrôler les différents composants matériels, les recenser, les mettre en marche lors de l'initialisation de l'ordinateur, etc.
Le Noyau permet en partie de faire le lien entre le matériel et la machine par l'intermédiaire de drivers.
Le noyau est le coeur du système, il gère la RAM, le framebuffer pour des écritures sur les disques dur. Il gère les entrées/sorties puis les processus et le système de fichiers

### Compilation du noyau

Dans la mesure où le code source du noyau Linux contient une très grande quantité de fonctionnalités, l'utilisateur peut choisir de n'intégrer que celles qui lui sont utiles ou les mieux adaptées (de nombreuses fonctionnalités sont concurrentes) : c'est l'étape de configuration du noyau.

L'étape la plus importante de la compilation d'un noyau personnalisée est la configuration du noyau. Les options de configuration sont déclarées dans le fichier *.config*, chacun correspond à une fonctionnalité du noyau, qu'on décide d'utiliser ou non. Trois choix sont généralement possibles :
- Y : la fonctionnalité est compilée et implantée dans l'image du noyau
- M : la fonctionnalité est compilée comme module
- N : la fonctionnalité est ignorée

Certaines options consistent en un choix binaire : la fonctionnalité est incluse dans l'image noyau ou n'est pas compilée.

Il existe plusieurs outils pour régler la configuration :

- make config : programme en mode texte qui énumère toutes les options et demande d'entrer son choix
- make menuconfig : utilitaire en mode texte écrit avec ncurses, il permet une navigation plus aisée dans la configuration
- make gconfig : outil graphique basé sur GTK+
- make xconfig : outil graphique basé sur Qt
- make defconfig : outil permettant de récupérer les paramètres de configuration par défaut du noyau. Ces paramètres sont donnés par les développeurs du noyau à chaque nouvelle sortie du noyau.
- make oldconfig : outil permettant de récupérer les paramètres de configuration d'une ancienne version du noyau afin de ne pas recommencer la configuration à zéro.
- make olddefconfig : outil permettant de récupérer les paramètres de configuration par défaut du noyau et de mettre les autres paramètres par défaut.
- make localmodconfig : outil permettant de récupérer les paramètres de configuration du noyau tournant actuellement sur la machine afin de ne charger que les modules nécessaires.


Fabriquer les binaires du kernel dépend de l'architecture cible.
Si le code est compilé sur l'architecture cible alors il n'y a pas besoin de faire de cross compilation.
Sinon il faut penser à adapter le make avec le compilateur adéquat à la cible.

### Construire le kernel sur l'architecture cible
Pour commencer il faut copier la config de la carte cible pour ce fait, on récupère la config qui est disponible dans le boot:
```
cp /boot/config-$(uname -r) .config
```

Pour accélérer la compilation mettre le nombre de coeur maximum que possède le processeur :
```
make -j$(nproc)
make install -j$(nproc)
make modules_install -j$(nproc)
```
Permettent respectivement d'installer l'image du noyau et ses modules.

Pour permettre l'amorçage du système avec la nouvelle image de noyau, il est nécessaire de configurer le chargeur de démarrage (LILO, GRUB) pour qu'il exécute l'image du noyau au démarrage. Avec (GRUB, GRUB2) la commande ```update-grub``` automatise la configuration.

## Arborescence

- bin : contient des programmes (exécutables) susceptibles d'être utilisés par tous les utilisateurs de la machine. (contient les commandes ls,mv,cp etc ...)

- boot : pour bootstrap fichiers permettant le démarrage de Linux. Contient le noyau.

- dev : Pour devices : fichiers contenant les périphériques. Ce dossier contient des sous-dossiers qui « représentent » chacun un périphérique. On y retrouve ainsi par exemple le fichier qui représente le lecteur CD.

- etc : Pour Editable Text Configuration : fichiers de configuration : liste des utilisateurs locaux, configuration du serveur web , la config de démarrage etc... 

- home : répertoires personnels des utilisateurs. On en a déjà parlé un peu avant : c'est dans ce dossier que vous placerez vos fichiers personnels, à la manière du dossierMes documentsde Windows.

Chaque utilisateur de l'ordinateur possède son dossier personnel. Par exemple, dans mon cas mon dossier personnel se trouve dans/home/kasi/. S'il y avait un autre utilisateur (appelons-le Patrick) sur mon ordinateur, il aurait eu droit lui aussi à son propre dossier :/home/patrick/.

- lib/lib64 : dossier contenant les bibliothèques partagées (généralement des fichiers.so) utilisées par les programmes essentiel au fonctionnement . C'est en fait là qu'on trouve l'équivalent des.dll de Windows.

- media : lorsqu'un périphérique amovible (comme une carte mémoire SD ou une clé USB) est inséré dans votre ordinateur, Linux vous permet d'y accéder à partir d'un sous-dossier demedia. On parle de montage.

- mnt : c'est un peu pareil que media, mais pour un usage plus temporaire.

- opt : optionnel : répertoire utilisé pour les add-ons de programmes.

- proc : pour processus : contient des informations système. Les fichiers qui sont dans ce dossier "n'existe pas" : c'est le noyau qui me présente sous forme de fichier les informations. Son contenue est totalement dynamique.
La commande ps utilise le contenu de /proc pour sortir les données: les numéros des dossiers correspondent au processus en cours d'utilisation sur la machine (PID)

- root : c'est le dossier personnel de l'utilisateur « root ». Normalement, les dossiers personnels sont placés danshome, mais celui de « root » fait exception. En effet, comme je vous l'ai dit dans le chapitre précédent, « root » est le superutilisateur, le « chef » de la machine en quelque sorte. Il a droit à un espace spécial.

- sbin : contient des programmes systèmes importants. 

- tmp : dossier temporaire utilisé par les programmes pour stocker des fichiers. Usage ponctuelle : car son contenue est supprimé au reboot du système.

- usr : c'est un des plus gros dossiers, dans lequel vont s'installer la plupart des programmes demandés par l'utilisateur et bibliothèques non essentiels.

- var : ce dossier contient des données « variables », souvent des logs (traces écrites de ce qui s'est passé récemment sur l'ordinateur). Contient les fichiers qui évoluent lors du fonctionnement de la machine. (Base de donnée/Serveur web etc ...)

### /boot

C'est le dossier système lié au démarrage de l'OS.
Il stocke :

- Les fichiers de configuration de grub dans /boot/grub/grub.cfg
- Les fichiers images du kernel Linux (noyau Linux)
- initrd (INITial RamDisk) - il contient les pilotes minimaux pour accéder au disque dur durant le démarrage du PC
- System.map : tableau de symbôle du noyau avec les adresses mémoires
- vmlinux : c'est le fichier du noyau Linux.

### /etc
Il stocke les fichiers de configurations du système ainsi que des applications.
Ainsi, on trouve un sous-dossier par application.
Parmi les sous-dossiers /etc importants :

- /etc/init.d et /etc/default : les fichiers liés aux daemons Linux
- /etc/password, /etc/group, /etc/shadow : les fichiers de configuration des utilisateurs Linux.
- /etc/hosts : le fichier HOSTS de Linux
- /etc/network : dossier de configuration réseau. L'emplacement peut varier selon la distribution.
- /etc/pam.conf et /etc/pam.d : la configuration des services d'authentification à travers Linux Pluggable Authentication Modules (PAM).
- /etc/sudoers et /etc/sudoers.d : la configuration de sudo.
- /etc/sysctl.conf et /etc/sysctl.d les fichiers de configuration de démarrage du noyau Linux.
- /etc/resolv.conf : la configuration des DNS Linux.

C'est un dossier système Linux très important pour le fonctionnement général du système d'exploitation.
Certains fichiers de configuration sont aussi liés à la configuration.
Ainsi, les utilisateurs ne doivent pas pouvoir écrire ou lire ces fichiers car ils peuvent modifier la configuration Linux.

### /dev
/dev
Le répertoire système /dev stocke les fichiers des périphériques à travers udev.
udev est un gestionnaire de périphériques de Linux.
Ce dernier monte de manière dynamique les périphériques utilisés sur le PC.
Mais on peut créer des règles pour imposer des configurations.
Par exemple, l'ordre des interfaces si vous avez plusieurs cartes réseaux (eth0, eth1).
Ou encore même chose sur l'ordre des disques et leurs numérotations.

### /proc

C'est un pseudo-système de fichiers basé sur procfs (process file system).
Il stocke des données du noyau que les applications peuvent utilisés.
On peut aussi y trouver des fichiers de configurations que l'on peut modifier directement.
Mais pour une persistance au démarrage, il faut modifier les fichier /etcsysctl.conf et /etc/sysctl.d ou utiliser la commande sysctl.

- /proc/cpuinfo : les informations CPU. Par exemple la commande lshw peut utiliser pour donner la configuration CPU.
- /proc/meminfo : stocke les informations sur mémoire libre, utilisés, etc. Les commandes top, freemem peuvent utiliser ce fichier.
- /proc/net : les données liées à l'utilisation réseau par protocole. Les commandes ifconfig, iftop peuvent s'en servir.
- /proc/diskstats et /proc/partitions : l'état des disques et partitions de disque.
- /proc/swaps : stocke les partitions SWAP.
- /proc/PID/ : les PID des applications ouvertures utilisés par exemple par top ou ps.

Enfin les paramètres du noyau se trouve dans /proc/sys/
Par exemple /proc/sys/net stocke la configuration réseau du noyau.
Souvent il s'agit de fichier avec des valeurs parfois de type boolean 0 ou 1.
Ainsi par exemple pour activer le routage entre les interfaces réseaux, on peut utiliser la commande :
```
echo 1 >/proc/sys/net/ipv4/ip_forward
```

Mais la configuration n'est pas persistante au redémarrage.

### /usr

Le répertoire système /usr stocke les données des applications des utilisateurs.
C'est donc en général des applications supplémentaires installées à partir du système de package de la distribution ou compilées.

On y trouve alors les sous-dossiers suivants :

- /usr/bin : stocke les exécutables et binaires des applications
- /usr/lib : le dossier des librairies utilisées par les applications
- /usr/local : les applications compilées. On retrouve alors la même structure de répertoire.
- /usr/share : le dossier avec les fichiers qui peuvent être partagés à toutes les architectures (i386, amd64, etc).
- /usr/src : les sources des applications que l'on peut compiler

### /var

Ce dossier système stocke des données variables.
Voici les principaux sous-répertoire de /var

- /var/log : les journaux et logs du système et des applications
- /var/lock : Les fichiers LCK. de verrous pour les ressources, périphériques partagés
- /var/run : Des fichiers liés aux applications en cours de fonctionnement. Par exemple, on peut y trouver le PID de l'application.
- /var/mail : les mails des utilisateurs
- /var/cache : dossiers et fichiers de cache. Par exemple apt peut y stocker les packages pour installer ou mettre à jour le système et les applications. On trouve aussi les documents et man des applications dans /var/cache/man.

## Raccourci Clavier

- Ctrl + L : Efface le contenu de la console. Utile pour faire un peu de ménage quand votre console est encombrée, ou quand votre boss passe derrière vous et que vous n'aimeriez pas qu'il voie ce que vous étiez en train de faire.

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

Utiliser un nano intelligent (souris et indentation automatique) : 

nano -miA source.txt
Créer un alias : nano ~/.bashrc
Mettreleclavierenfr : setxkbmap fr

CAT : (mettre des | entre)

cut -d " " -f 1 // Récupérer le premier champs du fichier séparé par " "


sort | uniq -c //Compter le nombre d'occurence.
sort //Trier
sort -u // Trier et enlever les doublons

afficher le premier élément d'une recherche (séparé par ":")
awk -F: '{print $1}'

grep ... //pour récupérer les lignes avec ceci.
grep -oP '".*?"' //Rechercher tout les mots entre guillements
grep ... | grep ... //Pour faire avec 2 recherches.
uniq //Pour afficher qu'une seule occurence.

python -m SimpleHTTPServer <PORT>

Installer sa carte graphique sur sa VM :
sudo apt install -y nvidia-driver nvidia-cuda-toolkit

Exemples : Recherche le mot categories et les scripts nse correspondant dans le repertoire : /usr/share/nmap/scripts/
grep -r categories /usr/share/nmap/scripts/*.nse

# Références
- https://tldp.org/LDP/lkmpg/2.6/lkmpg.pdf

Enumération dyn. du rep. Desktop : watch -n 2 ls /home/kasi/Desktop/

youtube-dl --extract-audio --audio-format mp3
