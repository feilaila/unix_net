
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
char *sock_ntop(const struct sockaddr *sockaddr,socklen_t *addrlen);

int sock_bind_wild(int sockfd,int family);
int sock_cmp_addr(const struct sockaddr *addr1,const struct sockaddr *addr2,socklen_t addrlen);
int sock_cmp_port(const struct sockaddr *addr1,const struct sockaddr *addr2,socklen_t addrlen);
int sock_get_port(const struct sockaddr *addr,socklen_t addrlen);
char *sock_ntop_host(const struct sockaddr *addr,socklen_t addrlen);
void sock_set_addr(const struct sockaddr *addr,socklen_t addrlen,void *ptr);
void sock_set_port(const struct sockaddr *addr,socklen_t addrlen,int port);
void sock_set_wild(const struct sockaddr *addr,socklen_t addrlen);

ssize_t readn(int fd,void *ptr,size_t len);
ssize_t writen(int fd,const void *buff,size_t len);
ssize_t readline(int fd,void *buff,size_t len);