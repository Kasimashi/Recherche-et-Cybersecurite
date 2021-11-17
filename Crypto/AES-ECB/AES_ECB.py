from Crypto.Cipher import AES
 
key = 'abcdefghijklmnop'
 
cipher = AES.new(key, AES.MODE_ECB)
msg =cipher.encrypt('TechTutorialsX!!TechTutorialsX!!')
print (type(msg))
 
print(msg.encode("hex"))
 
decipher = AES.new(key, AES.MODE_ECB)
print(decipher.decrypt(msg))