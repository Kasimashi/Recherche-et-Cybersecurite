# Tricks Linux

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
