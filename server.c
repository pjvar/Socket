#include "t_net.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc,char *argv[]){
    int sfd,cfd;
    SA4 client;
    socklen_t  cli_len;
    char IP[32];

    sfd=t_sock_b(4444);
    if(sfd==-1) return -1;
    
    //将sfd设置为被动连接
    listen(sfd,4);
    while(1){
        //从未决连接队列中，取出一个连接处理，返回一个和客户端的连接
        //cfd=accept(sfd,NULL,NULL);
        cli_len=sizeof(client);
        cfd=accept(sfd,(SA *)&client,&cli_len);
        if(cfd==-1){
            perror("accept");
            return -1;
        }
        printf("%s\n",inet_ntop(AF_INET,&client.sin_addr,IP,32));
        pid_t pid=fork();
        if(pid==-1){
            perror("fork");
            return -1;
        }
        if(pid==0){
            close(sfd);
            //业务处理
            doit(cfd);
            //关闭本次连接
            close(cfd);
            exit(0);
        }else{
            close(cfd);
            waitpid(-1,NULL,WNOHANG);
        }

    }
    return 0;
}
