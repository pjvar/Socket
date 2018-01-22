#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>

int  main(int argc,char *argv[]){
    int fd;
    struct sockaddr_in serv;
    char buf[128];
    char msg[128];
    char *s;
    //创建一个通讯端点，返回一个fd
    fd=socket(AF_INET,SOCK_STREAM,0);
    if(fd==-1){
        perror("socket");
        return -1;
    }
    //初始化服务器的参数
    serv.sin_family=AF_INET;
    serv.sin_port=htons(4444);
    //要知道服务器的ip地址，字符串格式。127.0.0.1
    //inet_pton(AF_INET,"127.0.0.1",&serv.sin_addr);
    inet_pton(AF_INET,argv[1],&serv.sin_addr);
    //使用这个fd连接服务器的ip地址和端口号
    int c=connect(fd,(struct sockaddr *)&serv,sizeof(serv));
    if(c==-1){
        perror("connect");
        return -1;
    }
    bzero(msg,128);
    while((s=gets(msg))!=NULL){
        //使用fd向服务器发送数据
        write(fd,msg,strlen(msg));
        bzero(buf,128);
        //阻塞等待服务器端的响应消息
        int r=read(fd,buf,128);
        bzero(msg,128);
        if(strcmp(buf,"EXIT")==0)break;
        //将获取到的响应消息输出到显示器
        write(1,buf,r);
        printf("\n");
    }
    //关闭本次连接
    close(fd);
    return 0;
}
