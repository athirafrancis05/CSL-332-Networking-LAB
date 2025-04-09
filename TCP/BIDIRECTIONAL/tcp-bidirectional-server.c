#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    char buf[100];
    int server_sock, client_sock;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(3003);

    bind(server_sock, (struct sockaddr*)&server, sizeof(server));
    listen(server_sock, 5);
    client_sock = accept(server_sock, (struct sockaddr*)&client, &len);

    while (1) {
        recv(client_sock, buf, sizeof(buf), 0);
        if (strcmp(buf, "exit\n") == 0) break;
        printf("Client from msg: %s", buf);
        printf("Msg to client: ");
        fgets(buf, sizeof(buf), stdin);
        send(client_sock, buf, strlen(buf), 0);
    }

    close(client_sock);
    close(server_sock);
    return 0;
}
