#include <stdio.h>
#include <winsock2.h>

using namespace std;

int main(int argc, char** argv) {
    SOCKET server;
    WSADATA wsaData;
    int socket_startup_error, clilen;
    struct sockaddr_in server_name, client_name;

    socket_startup_error = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if(socket_startup_error) {
        printf("Unable to start socket");
        printf("Error code: %d", socket_startup_error);
        return 0;
    }

    server_name.sin_family = AF_INET;
    server_name.sin_addr.s_addr = inet_addr("0.0.0.0");
    server_name.sin_port = htons(8000);

    server = socket(AF_INET, SOCK_STREAM, 0);
    if(bind(server, (const sockaddr *)&server_name, sizeof(server_name))) {
        printf("Unable to bind socket\n");
        printf("Error code: %d", WSAGetLastError());
        return 0;
    }
    listen(server, 0);
    accept(server, (struct sockaddr *)&client_name, &clilen);

    printf("Received connection");

    return 0;
}