#Le chiffrement de Vigenère
On associe à chaque lettre une autre lettre (sans ordre fixe ou règle générale).
Par exemple :
A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
F Q B M X I T E P A L W H S D O Z K V G R C N Y J U

Par exemple :
ETRE OU NE PAS ETRE TELLE EST LA QUESTION
devient :
XGKX DR SX OFV XGKX GXWWX XVG WF ZRXVGPDS

#Méthode d'attaque:
Mathématiquement, le choix d’une clé revient au choix d’une bijection de l’ensemble : A, B, . . . , Z vers le même ensemble A, B, . . . , Z
	
Il y a 26! choix possibles. En effet pour la lettre A de l’ensemble de départ, il y a 26 choix possibles (nous avions choisi F), pour B il reste 25 choix possibles (tout sauf F qui est déjà choisi), pour C il reste 24 choix... enfin pour Z il ne reste qu’une seule possibilité, la seule lettre non encore choisie. Au final il y a : 26 × 25 × 24 × ··· × 2 × 1 soit 26! choix de clés. Ce qui fait environ 4 × 1026 clés. Il y a plus de clés différentes que de grains de sable sur Terre ! Si un ordinateur pouvait tester 1 milliard de clés par seconde, il lui faudrait alors 12 milliards d’années pour tout énumérer.

Attaque statistique
La principale faiblesse du chiffrement mono-alphabétique est qu’une même lettre est toujours chiffrée de la même façon. Par exemple, ici E devient X. Dans les textes longs, les lettres n’apparaissent pas avec la même fréquence. Ces fréquences varient suivant la langue utilisée. En français, les lettres les plus rencontrées sont dans l’ordre :
E S A I N T R U L O D C P M V Q G F H B X J Y Z K W avec les fréquences (souvent proches et dépendant de l’échantillon utilisé) :
E S A I N T R U L O D
14.69% 8.01% 7.54% 7.18% 6.89% 6.88% 6.49% 6.12% 5.63% 5.29% 3.66%

Voici la méthode d’attaque : dans le texte crypté, on cherche la lettre qui apparaît le plus, et si le texte est assez long cela devrait être le chiffrement du E, la lettre qui apparaît ensuite dans l’étude des fréquences devrait être le chiffrement du S, puis le chiffrement du A... On obtient des morceaux de texte clair sous la forme d’une texte à trous et il faut ensuite deviner les lettres manquantes.
Par exemple, déchiffrons la phrase :
LHLZ HFQ BC HFFPZ WH YOUPFH MUPZH
On compte les apparitions des lettres :
H : 6 F : 4 P : 3 Z : 3
On suppose donc que le H crypte la lettre E, le F la lettre S, ce qui donne
*E** ES* ** ESS** *E ***SE ****E
D’après les statistiques P et Z devraient se décrypter en A et I (ou I et A). Le quatrième mot "HFFPZ", pour l’instant décrypté en "ESS**", se complète donc en "ESSAI" ou "ESSIA". La première solution semble correcte ! Ainsi P crypte A, et Z crypte I. La phrase est maintenant :
*E*I ES* ** ESSAI *E ***ASE **AIE
En réfléchissant un petit peu, on décrypte le message :
CECI EST UN ESSAI DE PHRASE VRAIE
