#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 3003
#define BUFFER_SIZE 1024
int main()
{
struct sockaddr_in server = {AF_INET, htons(PORT), INADDR_ANY};
int sock_d = socket(AF_INET, SOCK_STREAM, 0);
bind(sock_d, (struct sockaddr *)&server, sizeof(server));
listen(sock_d, 1);
int new_sock = accept(sock_d, NULL, NULL);
FILE *file = fopen("received_file.txt", "w");
if (!file)
{
perror("File write error");
return 1;
}
char buffer[BUFFER_SIZE];
int bytes;
while ((bytes = recv(new_sock, buffer, BUFFER_SIZE, 0)) > 0)
fwrite(buffer, 1, bytes, file);
fclose(file);
close(new_sock);
close(sock_d);
}
