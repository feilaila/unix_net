#include "common.h"
#include "helloserver.h"
#include <stdlib.h>
pid_t Fork();
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
        if(Fork()==0){
            close(listenfd);

            str_echo(connfd);

            close(connfd);
            exit(0);
        }
        close(connfd);
    }
    
    return 0;
}

void str_echo(int fd){
     int n;
     char buff[1024];
     while((n=read(fd,buff,1024)) >0){
         printf(buff);
         write(fd,buff,n);
     }
}
pid_t Fork(){
    pid_t pid;
    if((pid=fork())==-1){
          printf(strerror(errno));
          printf("fork err:%d",errno);
          return -1;
    }
    return pid;
}