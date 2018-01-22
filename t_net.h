#ifndef T_NET_H_
#define T_NET_H_
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
//类型的定义
typedef struct sockaddr SA;
typedef struct sockaddr_in SA4;

int t_sock_b(int);

#endif
