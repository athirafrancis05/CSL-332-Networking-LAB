#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    char buf[100];
    int client_sock;
    struct sockaddr_in server;

    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(1234);

    connect(client_sock, (struct sockaddr*)&server, sizeof(server));
    printf("Client to Server: ");
    fgets(buf, sizeof(buf), stdin);
    send(client_sock, buf, strlen(buf), 0);
    close(client_sock);
    return 0;
}
