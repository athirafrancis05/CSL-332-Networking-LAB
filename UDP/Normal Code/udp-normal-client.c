#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
    char buf[100];
    int sock_desc;
    struct sockaddr_in server;
    sock_desc = socket(AF_INET, SOCK_DGRAM, 0); // Use SOCK_DGRAM for UDP
    if (sock_desc == -1) {
        printf("Error in socket creation");
        exit(1);
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(1234);    
    printf("\nEnter data to Server: ");
    fgets(buf, 100, stdin);
    sendto(sock_desc, buf, strlen(buf), 0, (struct sockaddr *)&server, sizeof(server));         
    close(sock_desc);
    return 0;
}
