#ifndef TCPCLIENT_H
#define TCPCLIENT_H

struct tcp_client {
    struct tcp_client* next;
    struct sockaddr_in* cl_sockaddr;
    int open_fd;
};

void write_msg(struct tcp_client*, char* msg);
#endif
