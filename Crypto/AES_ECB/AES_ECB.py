#!/usr/bin/python3

from Crypto.Cipher import AES
 
key = '\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'
 
cipher = AES.new(key, AES.MODE_ECB)
msg =cipher.encrypt('TOTOTOTOTOTOTOTO')
print (type(msg))
 
print(msg.hex())
 

decipher = AES.new(key, AES.MODE_ECB)
print(decipher.decrypt(msg))
