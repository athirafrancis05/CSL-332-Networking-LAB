#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <arpa/inet.h>
#define PORT 8080
#define MAX_FRAMES 10
int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1, addrlen = sizeof(address);
    int frame;
    bool received[MAX_FRAMES] = {false};
    int received_order[MAX_FRAMES]; // For storing order of received frames
    int index = 0;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    printf("Receiver ready. Waiting for frames...\n");
    while (1) {
        read(new_socket, &frame, sizeof(frame));
        if (frame == -1) break;
        if (!received[frame]) {
            printf("Received Frame %d. Sending ACK...\n", frame);
            received[frame] = true;
            received_order[index++] = frame;
        } else {
            printf("Duplicate Frame %d. ACK Resent.\n", frame);
        }
        write(new_socket, &frame, sizeof(frame)); // ACK
    }
    printf("\n=== Final Received Frames (in order) ===\n[ ");
    for (int i = 0; i < index; i++) {
        printf("%d ", received_order[i]);
    }
    printf("]\n");
    close(new_socket);
    close(server_fd);
    return 0;
}
