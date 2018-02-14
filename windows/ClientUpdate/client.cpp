#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#pragma comment (lib, "Ws2_32.lib")

int sendMessage(struct sockaddr_in serverAddr, char* msg, size_t numBytes);
void switchEndianFormat(void* bytes, size_t numBytes);

int main(int argc, char** argv) {
    WSADATA wsaData;
    int socket_startup_error;

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

        if(sendMessage(server, buffer, strlen(buffer)) < 0) {
            printf("Could not send message\n");
        }
    }

    WSACleanup();

    return 0;
}



int sendMessage(struct sockaddr_in serverAddr, char* msg, size_t numBytes) {
    int connect_response;
    SOCKET client = socket(AF_INET, SOCK_STREAM, 0);
    connect_response = connect(client, (const struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if(connect_response < 0) {
        return -1;
    }
    else {
        char buffer[256];
        int numBytesBuffer = numBytes;
        switchEndianFormat(&numBytesBuffer, sizeof(int));
        send(client, (char*)&numBytesBuffer, 4, 0);
        send(client, msg, numBytes, 0);

        memset(buffer, 0, sizeof(buffer));
        recv(client, (char*)&numBytesBuffer, sizeof(int), 0);
        switchEndianFormat(&numBytesBuffer, sizeof(int));
        recv(client, buffer, numBytesBuffer, 0);

        printf("Expected to receive %d bytes\n", numBytesBuffer);
        printf("Message:\n");
        printf("%s\n", buffer);

        return 0;
    }
}


void switchEndianFormat(void* bytes, size_t numBytes) {
    int i;
    char tempStorage;
    char* pointer = (char*)bytes;

    for(i = 0; i < numBytes/2; i++) {
        tempStorage = pointer[i];
        pointer[i] = pointer[numBytes - i - 1];
        pointer[numBytes - i - 1] = tempStorage;
    }
}