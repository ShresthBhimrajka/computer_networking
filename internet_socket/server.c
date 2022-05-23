#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include<string.h>

int main()
{
    int server_sockfd, client_sockfd;
    int server_len,len,p;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = 9734;
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
    listen(server_sockfd, 5);
    while(1) {
        char msg[2048],msg1[2048];
        printf("server waiting\n");
        len = sizeof(client_address);
        client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address,&len);
        read(client_sockfd, &msg, sizeof(msg));
        fgets(msg1,2048,stdin);
        strcat(msg,msg1);
        p=sizeof(msg);
        write(client_sockfd, &msg,p);
        close(client_sockfd);
    }
}