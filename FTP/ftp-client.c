#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#define PORT 3003
#define BUFFER_SIZE 1024
int main()
{
struct sockaddr_in server = {AF_INET, htons(PORT),inet_addr("127.0.0.1")};
int sock_d = socket(AF_INET, SOCK_STREAM, 0);
connect(sock_d, (struct sockaddr *)&server, sizeof(server));
char filename[100], buffer[BUFFER_SIZE];
printf("Enter file name: ");
scanf("%s", filename);
FILE *file = fopen(filename, "r");
if (!file)
{
perror("File open failed");
return 1;
}
size_t bytesRead;
while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) > 0)
send(sock_d, buffer, bytesRead, 0);
fclose(file);
close(sock_d);
}
