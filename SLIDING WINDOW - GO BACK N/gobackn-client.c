#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#define WINDOW_SIZE 4
#define MAX_PACKETS 10
#define PORT 3003

int main() {
    int sock_desc;
    struct sockaddr_in receiver_addr;
    socklen_t addr_len = sizeof(receiver_addr);
    char packets[MAX_PACKETS][20];
    char ack[10];
    int base = 0, next_seq_num = 0;

    // Create UDP socket
    sock_desc = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_desc == -1) {
        perror("Socket creation failed");
        exit(1);
    }
    // Configure receiver address
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(PORT);
    receiver_addr.sin_addr.s_addr = INADDR_ANY;

    // Prepare packets
    for (int i = 0; i < MAX_PACKETS; i++) {
        sprintf(packets[i], "Packet %d", i);
    }
    printf("Starting Go-Back-N Transmission...\n");
    while (base < MAX_PACKETS) {
        // Send packets within the window
        while (next_seq_num < base + WINDOW_SIZE && next_seq_num < MAX_PACKETS) {
            sendto(sock_desc, packets[next_seq_num], strlen(packets[next_seq_num]) + 1, 0,
                   (struct sockaddr *)&receiver_addr, addr_len);
            printf("Sent: %s\n", packets[next_seq_num]);
            next_seq_num++;
        }

        // Wait for acknowledgment
        int bytes_received = recvfrom(sock_desc, ack, sizeof(ack), 0, (struct sockaddr *)&receiver_addr, &addr_len);
        if (bytes_received > 0) {
            ack[bytes_received] = '\0';
            int ack_num = atoi(ack);
            printf("Received ACK: %d\n", ack_num);

            // Slide the window forward
            if (ack_num >= base) {
                base = ack_num + 1;
            }
        } else {
            // If no ACK is received, retransmit all packets in the window
            printf("Timeout! Retransmitting from Packet %d\n", base);
            next_seq_num = base;
        }
    }

    printf("All packets sent successfully.\n");
    close(sock_desc);
    return 0;
}
