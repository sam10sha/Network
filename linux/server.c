#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char** argv) {
    if(argc < 2) {
        printf("Usage %s portnumber\n", *argv);
        return 0;
    }

    int server_fd, client_fd, shut_down;
    socklen_t cli_len;
    char buffer[100];
    struct sockaddr_in server_addr, cli_addr;

    shut_down = 0;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Error binding to socket\n");
        return 0;
    }
    listen(server_fd, 5);

    do {
        client_fd = accept(server_fd, (struct sockaddr *)&cli_addr, &cli_len);
        memset(buffer, 0, sizeof(buffer));
        recv(client_fd, buffer, sizeof(buffer)-1, 0);
        printf("Message: %s\n", buffer);
        if(!strcmp(buffer, "halt"))
            shut_down = 1;
        memset(buffer, 0, sizeof(buffer));
        strcpy(buffer, "Received");
        send(client_fd, buffer, strlen(buffer), 0);
	shutdown(client_fd, SHUT_RDWR);
    } while(!shut_down);

    shutdown(server_fd, SHUT_RDWR);

    return 0;
}
