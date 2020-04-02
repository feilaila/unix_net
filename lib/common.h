
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
char *sock_ntop(const struct sockaddr *sockaddr,socklen_t *addrlen);