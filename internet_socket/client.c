#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result,l;
    char msg[2048];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = 9734;
    len = sizeof(address);
    result = connect(sockfd, (struct sockaddr *)&address, len);
    if(result == -1)
    {
        perror("oops: client1");
        exit(1);
    }
    fgets(msg,200,stdin);
    l=sizeof(msg);
    write(sockfd, &msg, l);
    read(sockfd, &msg, l);
    printf("char from server = %s\n", msg);
    close(sockfd);
    exit(0);
}