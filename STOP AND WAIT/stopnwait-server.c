#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 3003
int main() {
    int sock_desc, client_sock;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);
    char buf[1024];
    char ack[10];
    int expected_packet = 0;// Create TCP socket
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc == -1) {
        perror("Socket creation failed");
        exit(1);
    } // Configure server
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY; // Bind the socket
    if (bind(sock_desc, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("Bind failed");
        exit(1);
    }// Listen for incoming connections
    if (listen(sock_desc, 1) == -1) {
        perror("Listen failed");
        exit(1);
    }
    printf("Waiting for a connection...\n");
    client_sock = accept(sock_desc, (struct sockaddr *)&client, &len);
    if (client_sock == -1) {
        perror("Accept failed");
        exit(1);
    }
    printf("Connection established. Receiving packets...\n");
    while (expected_packet < 5) { // Receive 5 packets for demonstration
        recv(client_sock, buf, sizeof(buf), 0);
        printf("Received: %s\n", buf); // Send acknowledgment
        sprintf(ack, "ACK %d", expected_packet);
        send(client_sock, ack, strlen(ack) + 1, 0);
        printf("Sent: %s\n", ack);
        expected_packet++;
    }
    printf("All packets received successfully.\n");
    close(client_sock);
    close(sock_desc);
    return 0;
}
