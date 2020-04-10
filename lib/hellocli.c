#include "common.h"
#include "hellocli.h"
#include <stdlib.h>
int main(int argc, char const *argv[])
{
    struct sockaddr_in sin;
    int sockfd;
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(argc < 2){
        printf("usage: hellocli:ipAddr");
       exit(0);
    }
    sin.sin_family = AF_INET;
    sin.sin_port = 8080;
    inet_pton(AF_INET,argv[1],&sin.sin_addr);
    if(connect(sockfd,(struct sockaddr *)&sin,sizeof(sin)) == -1){
         printf(strerror(errno));
         exit(0);
    }
    str_cli(sockfd,stdin);
    exit(0);
}
#define MAXLINE 1024
void str_cli(int fd,FILE *fp){

    char recvbuff[MAXLINE];
    char sendbuff[MAXLINE];
    while(fgets(sendbuff,MAXLINE,fp) !=NULL)
    {
        printf("size:%ld",strlen(sendbuff));
        write(fd,sendbuff,strlen(sendbuff));
        if(readline(fd,recvbuff,MAXLINE)<=0){
            printf(strerror(errno));
            return;
        }
        fputs(recvbuff,stdout);
    }
    
}