#include <stdio.h>
#include <stdlib.h>
#define BUCKET_SIZE 10
void leaky_bucket(int packets[], int n, int output_rate) {
int buffer = 0, i;
for (i = 0; i < n; i++) {
if (packets[i] + buffer > BUCKET_SIZE) {
printf("Packet loss = %d\n", (packets[i] + buffer) - BUCKET_SIZE);
buffer = BUCKET_SIZE;
} else {
buffer += packets[i];
}
printf("Buffer size = %d out of bucket size = %d\n", buffer, BUCKET_SIZE);
if (buffer >= output_rate) {
buffer -= output_rate;
} else {
buffer = 0;
}
}
}
int main() {
int n, i, output_rate;
printf("Enter the number of packets: ");
scanf("%d", &n);
int packets[n];
printf("Enter the packet sizes: ");
for (i = 0; i < n; i++) {
scanf("%d", &packets[i]);
}
printf("Enter the output rate: ");
scanf("%d", &output_rate);
leaky_bucket(packets, n, output_rate);
return 0;
}
