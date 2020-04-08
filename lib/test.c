#include "common.h"

int main(int argc, char const *argv[])
{
    struct  sockaddr_in sin;
    bzero(&sin,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(0x01020304);
    sin.sin_port=htons(8080);
    socklen_t len = sizeof(struct sockaddr_in);
    char *str;
    str=sock_ntop((struct sockaddr *)&sin,&len);
    printf(str);
    return 0;
}
