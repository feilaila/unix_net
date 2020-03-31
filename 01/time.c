#include "time.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/errno.h>

#define	SA	struct sockaddr
#define MAXLINE 2048
int main(int argc, char const *argv[])
{
    /* code */
    int sockfd,n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;
    if(argc != 2){
        printf("usage: c.out <IP address");
        exit(0);
    }
    if((sockfd = socket(AF_INET,SOCK_STREAM,0))<0){
        err_sys("socket err");
    }
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9999);
    if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr)<=0){
        printf("inet_pton err:%s",argv[1]);
        exit(1);
    }
    if(connect(sockfd,(SA *)&servaddr,sizeof(servaddr))<0){
        printf("connect err");
    }
    int i=0;
    while((n=read(sockfd,recvline,MAXLINE))>0){
        i++;
        recvline[MAXLINE]=0;
        if(fputs(recvline,stdout) == EOF){
            printf("fputs err");
            exit(0);
        }
    }
    printf("\ni:%d",i);
    if(n<0){
        printf("read error");
    }
    // printf("sockfd:%s",argv[1]);
    // printf("argv 0:%s",argv[0]);
    
    return 0;
}
