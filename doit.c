#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

void doit(int fd){
    char buf[128];
    int i,r;
    while(1){
        bzero(buf,128);
        r=read(fd,buf,128);
        for(i=0;i<r;i++)
            buf[i]=toupper(buf[i]);
        write(fd,buf,r);
        //printf("buf:%s\n",buf);
        if(strcmp(buf,"EXIT")==0)break;
    }

    return;

}
