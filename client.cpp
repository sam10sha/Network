#include <stdio.h>
#include <string.h>
#include <winsock2.h>

void replaceAll(char* str, char* oldstr, char* newstr);

void replace(char *str, char *newstr, int index, int numOverwrite);

int main(int argc, char** argv) {
    /* if(argc < 3) {
        printf("Usage: %s [address] [portnumber]\r\n", *argv);
        return 0;
    } */

    WSADATA wsaData;
    int socket_startup_error, connect_response;

    socket_startup_error = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if(socket_startup_error) {
        printf("Unable to start socket");
        printf("Error code: %d", socket_startup_error);
        return 0;
    }


    char ip_addr[25];
    char portnum[10];
    if(argc < 3) {
        printf("Enter the IP address: ");
        fgets(ip_addr, sizeof(ip_addr)-1, stdin);
        printf("Enter the port number: ");
        fgets(portnum, sizeof(portnum)-1, stdin);
    }
    else {
        memcpy(ip_addr, argv[1], strlen(argv[1]));
        memcpy(portnum, argv[2], strlen(argv[2]));
    }

    char buffer[100];
    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr((const char *)ip_addr);
    server.sin_port = htons(atoi(portnum));

    while(strcmp(buffer, "halt")) {
        memset(buffer, 0, 100);
        printf(">>> ");
        fgets(buffer, sizeof(buffer)-1, stdin);
        replaceAll(buffer, "\n", "\0");

        SOCKET client = socket(AF_INET, SOCK_STREAM, 0);
        connect_response = connect(client, (const struct sockaddr *)&server, sizeof(server));
        if(connect_response < 0)
            printf("Connect response: %d\r\n", WSAGetLastError());
        send(client, buffer, strlen(buffer), 0);
    }

    return 0;
}

void replace(char *str, char *newstr, int index, int numOverwrite) {

    int i, extension, increment;

    extension = (int)strlen(newstr) - numOverwrite;

    if(extension) {

        if(extension > 0) {

            i = (int)strlen(str) - 1;

            increment = -1;

        }

        else {

            i = index + numOverwrite;

            increment = 1;

        }


        while(index+numOverwrite <= i && i < (int)strlen(str)) {

            str[i+extension] = str[i];

            /* printf("%s\r\n", str); */

            i += increment;

        }

        if(extension < 0)

            memset(str+(int)strlen(str)+extension, 0, extension * -1);

    }

    memcpy((void *)(str+index), (const void *)newstr, strlen(newstr));

}



void replaceAll(char* str, char* oldstr, char* newstr) {

    int i;

    char buffer[100];


    for(i = 0; i < strlen(str) - strlen(oldstr) + 1; i++) {

        memset(buffer, 0, strlen(buffer));

        memcpy((void *)buffer, (const void *)(str+i), strlen(oldstr));

        if(!strcmp(buffer, oldstr))

            replace(str, newstr, i, (int)strlen(oldstr));

    }

}