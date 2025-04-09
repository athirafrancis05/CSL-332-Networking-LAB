#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 3003
#define MAX_PACKETS 10

int main() {
    int sock_desc;
    struct sockaddr_in receiver_addr, sender_addr;
    socklen_t addr_len = sizeof(sender_addr);
    char buf[20];
    int expected_seq_num = 0;

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

    // Bind the socket
    if (bind(sock_desc, (struct sockaddr *)&receiver_addr, sizeof(receiver_addr)) == -1) {
        perror("Bind failed");
        exit(1);
    }

    printf("Waiting for packets...\n");

    while (1) {
        // Receive packet
        int bytes_received = recvfrom(sock_desc, buf, sizeof(buf), 0, (struct sockaddr *)&sender_addr, &addr_len);
        if (bytes_received <= 0) {
            break;
        }

        buf[bytes_received] = '\0'; // Null-terminate the received data
        printf("Received: %s\n", buf);

        // Extract sequence number from packet
        int seq_num;
        sscanf(buf, "Packet %d", &seq_num);

        // Send acknowledgment if the packet is in order
        if (seq_num == expected_seq_num) {
            printf("Sending ACK: %d\n", seq_num);
            sprintf(buf, "%d", seq_num);
            sendto(sock_desc, buf, strlen(buf) + 1, 0, (struct sockaddr *)&sender_addr, addr_len);
            expected_seq_num++;
        } else {
            // Ignore out-of-order packets
            printf("Out-of-order packet. Expected: %d, Received: %d\n", expected_seq_num, seq_num);
        }

        if (expected_seq_num >= MAX_PACKETS) {
            break;
        }
    }

    printf("All packets received successfully.\n");
    close(sock_desc);
    return 0;
}
