#include "time.h"
#include <netinet/in.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#define MAXLINE 2048
#define	LISTENQ		1024
int main(int argc, char const *argv[])
{
    int listenfd,connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t ticks;
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(9999);
    bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    listen(listenfd,LISTENQ);
    for(;;){
        connfd = accept(listenfd,(struct sockaddr *)NULL,NULL);
        ticks = time(NULL);
        int i=0;
      
        snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));
        for(;i<strlen(buff);i++){
        write(connfd,&buff[i],1);

        }
        close(connfd);
    }
    return 0;
}
