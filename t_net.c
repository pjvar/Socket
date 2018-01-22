#include "t_net.h"

int t_sock_b(int port){
    int sfd;
    SA4 serv;
    sfd=socket(AF_INET,SOCK_STREAM,0);
    if(sfd==-1){
        perror("socket");
        return -1;
    }
    //初始化serv的成员
    serv.sin_family=AF_INET;
    serv.sin_port=htons(port);
    serv.sin_addr.s_addr=htonl(INADDR_ANY);
    //将sfd和服务器的ip地址和端口号绑定
    int b=bind(sfd,(SA *)&serv,sizeof(serv));
    if(b==-1){
        perror("bind");
        return -1;
    }
    return sfd;
}
