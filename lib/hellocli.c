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
        return 0;
    }
    sin.sin_family = AF_INET;
    sin.sin_port = 8080;
    inet_pton(AF_INET,argv[1],&sin.sin_addr);
    connect(sockfd,(struct sockaddr *)&sin,sizeof(sin));
    str_cli(sockfd,stdin);
    return 0;
}

void str_cli(int fd,FILE *fp){

    char buff[1204];
    while (fgets(buff,strlen(buff),fp) !=NULL)
    {
        writen(fd,buff,strlen(buff));
        if(readn(fd,buff,sizeof(buff))<=0){
            printf("server close;");
            return;
        }
        fputs(buff,stdout);
    }
    
}