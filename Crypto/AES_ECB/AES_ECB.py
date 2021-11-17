#!/usr/bin/python3

import binascii
from Crypto.Cipher import AES
 
key = b'\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'
buff = b'\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'

print("Key : ")
print(binascii.hexlify(key))

print("Buffer : ")
print(binascii.hexlify(buff))

cipher = AES.new(key, AES.MODE_ECB)
print("Encrypt:")
print(cipher.encrypt(buff).hex())
 
print("Decrypt:")
decipher = AES.new(key, AES.MODE_ECB)
print(decipher.decrypt(buff).hex())
