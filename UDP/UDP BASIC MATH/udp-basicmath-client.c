#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[100];
    int num1, num2;
    char op;
    socklen_t len;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1234);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    printf("Enter operation (e.g., 5 + 3): ");
    scanf("%d %c %d", &num1, &op, &num2);
    sprintf(buffer, "%d %c %d", num1, op, num2);
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    len = sizeof(server_addr);
    recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&server_addr, &len);
    printf("Result from server: %s\n", buffer);
    close(sockfd);
    return 0;
}
