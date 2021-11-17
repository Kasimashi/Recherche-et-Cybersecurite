# Table de routage Linux

Pour accéder à la table de routage sur linux il faut tapper la commande :
`ip route show`

Par exemple pour mon cas j'ai :
```
default via 192.168.1.254 dev eth1 
10.10.10.0/23 via 10.10.14.1 dev tun0 
10.10.14.0/23 dev tun0 proto kernel scope link src 10.10.14.15 
10.129.0.0/16 via 10.10.14.1 dev tun0 
192.168.1.0/24 dev eth1 proto kernel scope link src 192.168.1.157 
192.168.2.0/24 dev eth0 proto kernel scope link src 192.168.2.5
```

Ce qui veux dire que mon traffic qui n'est pas 192.168.1.0/24, 192.168.2.0/24, 10.10.14.0/23 etc ... est redirigé vers l'interface eth1 via le gateway 192.168.1.254

Pour modifier le traffic par défaut on peut supprimer cette ligne avec la commande :

`sudo ip route del default via 192.168.1.254 dev eth1`

Et par exemple passer par l'interface eth0 avec le gateway 192.168.2.254 avec la commande :

`sudo ip route add default via 192.168.2.254 dev eth0`


