CC=gcc
CFLAGS=-lcrypto -lssl

all: MD5

clean: 
	rm -rf MD5
	rm -rf MD5.o

MD5: MD5.o
	gcc MD5.c -o MD5 -L/usr/local/ssl/lib -lssl -lcrypto

