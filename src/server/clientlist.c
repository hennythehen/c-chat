#include "tcpclient.h"
#include "msgqueue.h"
#include "clientlist.h"
#include <stdlib.h>

void push_client(struct client_list* cl_list, struct tcp_client* tcp_cl) {
    if (cl_list->size == 0) {
        cl_list->head = tcp_cl;
        cl_list->tail = cl_list->head;
    }
    else {
        cl_list->tail->next = tcp_cl;
        cl_list->tail = cl_list->tail->next;
    }
    cl_list->size += 1;
}

/*
 * writes a message to all clients in list ecluding message originator
 */
int post_msg(struct client_list* cl_list, struct msg_queue* mq) {
    struct tcp_client* tmp;
    tmp = cl_list->head;
    struct msgc m;
    m = *(peek(mq));
    int i;
    for (i = 0; i < cl_list->size; i++) { 
        if (m.orig_fd != tmp->open_fd) {
            write_msg(tmp, m.msg);
        }
        tmp = tmp->next;
    } 
    pop(mq);

    return 0;
}
