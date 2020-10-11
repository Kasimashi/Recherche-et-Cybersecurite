## Chiffrement César
En cryptographie, le chiffrement par décalage, aussi connu comme le chiffre de César ou le code de César, est une méthode de chiffrement très simple utilisée par Jules César dans ses correspondances secrètes (ce qui explique le nom « chiffre de César »).

## C++
Ce programme est à compiler grâce à la commande suivante :
g++ src/main.cpp -o bin/ceaser_cipher_decipher.exe -Wall -Wextra -pedantic -std=c++17

## Python3 :
Pour executer le script :
python3 src/main.py


## Méthode d'attaque :
Pour l’attaque on parcourt l’intégralité de l’espace des clés : k varie de 0 à 25. Noter que pour décrypter les messages
On décrypte pour chaques clefs et on cherche à obtenir un mot qui a du sens.
