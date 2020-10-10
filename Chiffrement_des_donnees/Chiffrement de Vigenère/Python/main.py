#!/usr/bin/python3

def statistiques(phrase):
    liste_stat=[0 for x in range(26)]   # Une liste avec des 0
    for lettre in phrase:               # On parcourt la phrase
        i=ord(lettre)-65
        if (0<=i<26):                      #Si c'est une vraie lettre
            liste_stat[i]=liste_stat[i]+1
    return(liste_stat)

def vigenere(mot,cle):                  # Clé est du type [n_1,...,n_k]
    message_code=[]
    k = len(cle)                         #Longueur de la clé
    i=0                                  #Rang dans le bloc
    for lettre in mot:                   #Pour chaque lettre
        nomb=ord(lettre)-65              #Lettre devient nb de 0 à 25
        nomb_code=(nomb+cle[i])%26       #Vigenère:on ajoute n_i
        lettre_code=chr(nomb_code+65)    #On repasse aux lettres
        i=(i+1)%k                        #On passe au rang suivant
        message_code.append(lettre_code) #Ajoute lettre au message
    message_code="".join(message_code)   #Revient à chaine caractères
    return(message_code)
    
print(vigenere("COUCOU",[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25]))
