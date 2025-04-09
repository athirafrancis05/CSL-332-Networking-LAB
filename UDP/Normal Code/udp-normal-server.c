#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
    char buf[100];
    socklen_t len;
    int sock_desc;
    struct sockaddr_in server, client;
    sock_desc = socket(AF_INET, SOCK_DGRAM, 0); // Use SOCK_DGRAM for UDP
    if (sock_desc == -1) {
        printf("Error in socket creation");
        exit(1);
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(1234);
    if (bind(sock_desc, (struct sockaddr *)&server, sizeof(server)) == -1) {
        printf("Error in binding");
        exit(1);}
    len = sizeof(client);
    if (recvfrom(sock_desc, buf, 100, 0, (struct sockaddr *)&client, &len) == -1) {
            printf("Error in receiving");
            exit(1);
        }
    printf("Message from client is: %s", buf);
    close(sock_desc);
    return 0;
}
