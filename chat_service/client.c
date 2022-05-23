#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<pthread.h>
#include<termios.h>
#include<stdlib.h>

void *recv_thread(void *a);
void *send_thread(void *a);
int cfd;

int main()
{
    struct sockaddr_in cl;
    int n;
    pthread_t snd,rcv;
    cfd=socket(AF_INET,SOCK_STREAM,0);
    cl.sin_family=AF_INET;
    inet_aton("127.0.0.1",&(cl.sin_addr));
    cl.sin_port=htons(8760);
    connect(cfd,(struct sockaddr *)&cl,sizeof(cl));
    pthread_create(&snd,NULL,send_thread,NULL);
    pthread_create(&rcv,NULL,recv_thread,NULL);
    pthread_join(snd,NULL);
    pthread_join(rcv,NULL);
    close(cfd);
    return 0;
}

void *send_thread(void *a)
{
    int n;
    char str[200];
    while(1)
    {
        fgets(str,200,stdin);
        write(cfd,(void *)str,sizeof(str));
        if(strncmp(str,"bye",3)==0)
        exit(0);
    }
    pthread_exit(NULL);
}

void *recv_thread(void *a)
{
    int n;
    char str[200];
    while(1)
    {
        n=read(cfd,(void *)str,sizeof(str));
        if(n>0)
        {
            printf("Server: %s",str);
            fflush(stdout);
        }
        if(strncmp(str,"bye",3)==0)
        exit(0);
    }
    pthread_exit(NULL);
}