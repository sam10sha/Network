#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char** argv)
{
    printf("10.3.0.136 = %u\n", inet_addr("10.3.0.136"));

    return 0;
}