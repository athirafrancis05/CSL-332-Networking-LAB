#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[100];
    socklen_t len;
    int num1, num2, result=0;
    char op;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1234);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    len = sizeof(client_addr);
    recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_addr, &len);
    sscanf(buffer, "%d %c %d", &num1, &op, &num2);
    if (op == '+') result = num1 + num2;
    else if (op == '-') result = num1 - num2;
    else if (op == '*') result = num1 * num2;
    else if (op == '/') result = num1 / num2;    
    sprintf(buffer, "%d", result);
    sendto(sockfd, buffer, strlen(buffer) + 1, 0, (struct sockaddr*)&client_addr, len);
    memset(buffer, 0, sizeof(buffer));
    close(sockfd);
    return 0;
}
