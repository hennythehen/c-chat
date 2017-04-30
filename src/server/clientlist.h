#ifndef CLIENTLIST_H
#define CLIENTLIST_H
#include "tcpclient.h"
#include "msgqueue.h"

struct client_list {
    struct tcp_client* head;
    struct tcp_client* tail;
    int size;
};

void push_client(struct client_list*, struct tcp_client*);
int post_msg(struct client_list*, struct msg_queue*);
#endif
