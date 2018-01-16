#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char** argv) {
    if(argc < 3) {
        printf("Usage: %s ip address port number\n", *argv);
        return 0;
    }

    int client_fd, shut_down;
    char buffer[100];
    struct sockaddr_in server_addr;

    shut_down = 0;
    memset(buffer, 0, sizeof(buffer));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    do {
        memset(buffer, 0, strlen(buffer));
        printf(">>> ");
        fgets(buffer, sizeof(buffer)-1, stdin);
        buffer[strlen(buffer)-1] = '\0';
        if(!strcmp(buffer, "halt"))
            shut_down = 1;
        client_fd = socket(AF_INET, SOCK_STREAM, 0);
        if(connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            printf("Failed to connect to server\n");
            continue;
        }
        send(client_fd, buffer, strlen(buffer) + 1, 0);
        memset(buffer, 0, strlen(buffer));
        recv(client_fd, buffer, sizeof(buffer)-1, 0);
        if(strlen(buffer))
            printf("%s\n", buffer);
        shutdown(client_fd, SHUT_RDWR);
    } while(!shut_down);

    return 0;
}
