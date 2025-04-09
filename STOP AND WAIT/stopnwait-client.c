#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 3003
int main() {
    int sock_desc;
    struct sockaddr_in server;
    char buf[1024];
    char ack[10];
    int packet_num = 0;    // Create TCP socket
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc == -1) {
        perror("Socket creation failed");
        exit(1);
    }  // Configure server
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;  // Connect to the server
    if (connect(sock_desc, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("Connection to server failed");
        exit(1);
    }
    printf("Connected to server. Starting Stop-and-Wait Transmission...\n");
    while (packet_num < 5) { // Send 5 packets for demonstration
        sprintf(buf, "Packet %d", packet_num);
        send(sock_desc, buf, strlen(buf) + 1, 0);
        printf("Sent: %s\n", buf);    // Wait for acknowledgment
        recv(sock_desc, ack, sizeof(ack), 0);
        printf("Received ACK: %s\n", ack);
        packet_num++;
    }
    printf("All packets sent successfully.\n");
    close(sock_desc);
    return 0;
}
