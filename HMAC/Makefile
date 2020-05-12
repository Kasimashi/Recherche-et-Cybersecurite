CC=gcc
CFLAGS=-lcrypto -lssl

all: HMAC

HMAC: HMAC.o
	gcc HMAC.c -o HMAC -L/usr/local/ssl/lib -lssl -lcrypto

