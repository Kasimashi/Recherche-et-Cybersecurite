#include <stdio.h>
#include <stdlib.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <string.h>

#define KEY  ((unsigned char*)"\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b") //Clé de HACHAGE
/*
 * HMACGen FUNCTION TAKE ENTIRE FILE IN ARGUMENT WITH THE KEY AND RETURN HMAC
 */
void HMACGen(char* buffer,unsigned char* key, char* HMAC)
{
        unsigned char* result;
        unsigned int resultLen = 64;

        HMAC_CTX *ctx;

        ctx = HMAC_CTX_new();



        result = (unsigned char*) malloc(sizeof(char) * resultLen);

        HMAC_Init_ex(ctx, key, 16, EVP_sha256(), NULL); //Initialisation du contexte
		HMAC_Update(ctx, (const unsigned char *)  buffer,  strlen(buffer)); //permet de MAJ le contexte à chaque ligne qu’on lit dans le fichier
        HMAC_Final(ctx, result, &resultLen); //Utilise le contexte pour générer une string Hmac_sha256 (format raw 64 bytes…)
        HMAC_CTX_reset(ctx);

        for (int i=0; i!=resultLen; i++)
        {
			sprintf(&HMAC[i*2],"%02X", result[i]);
        }
        printf("\n");
        //sprintf("%02X",1);
        //sprintf(HMAC,"%X", result);
        printf("HMAC :%s",HMAC);
        free(result);
}

int main(void) {
	char HMAC[64];
	puts("This program encrypt a string in SHA256"); /* prints This program permit to rotate log files (50 lines max) and encrypt it in SHA256 */
	HMACGen("azerty",KEY,HMAC);
	return EXIT_SUCCESS;
}
