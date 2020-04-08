#include "common.h"

char * sock_ntop(const struct sockaddr *sa,socklen_t *len){
    char portstr[8];
    static char str[128];
    switch (sa->sa_family)
    {
    case AF_INET:
        {
            struct sockaddr_in *sin =(struct sockaddr_in *)sa;
            if(inet_ntop(AF_INET,&sin->sin_addr,str,sizeof(str)) == NULL){return NULL;}
            if(ntohs(sin->sin_port)!=0){
                snprintf(portstr,sizeof(portstr),":%d",ntohs(sin->sin_port));
                strcat(str,portstr);
            }
            return str;
        }
        break;
    
    default:
        break;
    }
    return NULL;
}

ssize_t readn(int fd,void *buff,size_t len){
    ssize_t nread;
    ssize_t nleft;
    char *ptr;
    nleft=len;
    ptr=buff;

    while(nleft>0){
        nread=read(fd,ptr,nleft);
        if(nread<0){
            if(errno==EINTR){
               continue;
            }else
            {
                return -1;
            }
        }else if (nread == 0)
        {
            break;
        }
        
        nleft -=nread;
        ptr +=nread;
    }
    return len -nleft;
}

ssize_t writen(int fd,const void *buff,size_t len){
    ssize_t nleft;
    ssize_t nwrite;
    const char *ptr;
    ptr = buff;
    nleft = len;
    while (nleft>0)
    {
        nwrite = write(fd,ptr,nleft);
        if(nwrite<0 && errno == EINTR){continue;}
        if(nwrite<0){return -1;}
        ptr +=nwrite;
        nleft -=nwrite;
    }
    return len - nleft;
}

ssize_t readline(int fd,void *buff,size_t len){
    char c;
    ssize_t i,rc;
    char *ptr = buff;
    for(i=0;i<len;i++){
        rc=read(fd,&c,1);
        if(rc==1){
            ptr[i]=c;
            if(c=='\n'){ptr[i]=0;return i;}
        }else if(rc==0){
            ptr[i]=0;
            return i;
        }else if (rc<0 && errno==EINTR)
        {
            continue;
        }else
        {
            return -1;
        }
    }
    return -1;
}

static int readcnt;
static char *readptr;
static char readbuf[2048];

static ssize_t my_read(int fd,char *ptr){

    if(readcnt<=0){
        while (readcnt<0)
        {
            readcnt = read(fd,readbuf,sizeof(readbuf));
            if(readcnt==0){
                return 0;
            }else if (readcnt<0 && errno==EINTR)
            {
                continue;
            }else if (readcnt<0)
            {
                return -1;
            }
            readptr=readbuf;
        }
        
    }
    readcnt--;
    *ptr = *readptr++;
    return 1;
}

ssize_t my_readline(int fd,void *buff,size_t len){
    char c;
    ssize_t i,rc;
    char *ptr = buff;
    for(i=0;i<len;i++){
        rc=my_read(fd,&c);
        if(rc==1){
            ptr[i]=c;
            if(c=='\n'){ptr[i]=0;return i;}
        }else if(rc==0){
            ptr[i]=0;
            return i;
        }else if (rc<0 && errno==EINTR)
        {
            continue;
        }else
        {
            return -1;
        }
    }
    return -1;
}
ssize_t my_readbuf(void **ptrptr){
    if(readcnt){
        *ptrptr = readptr;
    }
    return readcnt;
}