#include "common.h"
#include "helloserver.h"
int main(int argc, char const *argv[])
{
    int listenfd,connfd;
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = 8080;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(listenfd,(struct sockaddr *)&sin,sizeof(struct sockaddr_in));
    listen(listenfd,5);
    while (1)
    {
        connfd = accept(listenfd,NULL,NULL);
        if(fork()==0){
            close(listenfd);

            str_echo(connfd);

            close(connfd);
        }
        close(connfd);
    }
    
    return 0;
}

void str_echo(int fd){
     int n;
     char buff[1024];
     while((n=readn(fd,buff,sizeof(buff)))>0){
         writen(fd,buff,n);
     }
}