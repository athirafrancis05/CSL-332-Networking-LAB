#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <time.h>
#define PORT 8080
#define MAX_FRAMES 10
#define WINDOW_SIZE 4
bool acked[MAX_FRAMES] = {false};
int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    int data[MAX_FRAMES];
    // User input: simulate frame data
    printf("Enter %d frame values (integers):\n", MAX_FRAMES);
    for (int i = 0; i < MAX_FRAMES; i++) {
        scanf("%d", &data[i]);
    }
    srand(time(NULL));
    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    int base = 0, next_frame = 0, ack;
    while (base < MAX_FRAMES) {
         for (int i = 0; i < WINDOW_SIZE && (base + i) < MAX_FRAMES; i++) {
            int f = base + i;
            if (!acked[f]) {
                int frame_no = f;
                printf("Sending Frame %d: %d\n", frame_no, data[f]);
                write(sock, &frame_no, sizeof(frame_no));
            }
        }
        for (int i = 0; i < WINDOW_SIZE && (base + i) < MAX_FRAMES; i++) {
            int f = base + i;
            if (!acked[f]) {
                read(sock, &ack, sizeof(ack));
                if (rand() % 4 == 0) {
                    printf("ACK for Frame %d LOST\n", ack);
                } else {
                    printf("ACK for Frame %d RECEIVED\n", ack);
                    acked[ack] = true;
                }
            }
        }
        while (acked[base] && base < MAX_FRAMES) {
            base++;
        }
        sleep(1);
        printf("\n");
    }
    int end = -1;
    write(sock, &end, sizeof(end));
    printf("All frames sent and acknowledged.\n");
    printf("\n=== Final Frame Data Sent ===\n[ ");
    for (int i = 0; i < MAX_FRAMES; i++) {
        printf("%d ", data[i]);
    }
    printf("]\n");
    close(sock);
    return 0;
}
