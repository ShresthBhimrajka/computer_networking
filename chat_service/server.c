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
    struct sockaddr_in ser,cl;
    int sfd,len,i,n;
    pthread_t snd,rcv;
    len=sizeof(cl);
    sfd=socket(AF_INET,SOCK_STREAM,0);
    ser.sin_family=AF_INET;
    inet_aton("127.0.0.1",&(ser.sin_addr));
    ser.sin_port=htons(8760);
    n=bind(sfd,(struct sockaddr*)&ser,sizeof(ser));
    n=listen(sfd,1);
    cfd=accept(sfd,(struct sockaddr*)&cl,&len);
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
            printf("Client : %s",str);
            fflush(stdout);
        }
        if(strncmp(str,"bye",3)==0)
        exit(0);
    }
    pthread_exit(NULL);
}