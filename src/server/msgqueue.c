#include "msgqueue.h"
#include <stdlib.h>
#include <string.h>

void new_msg(struct msg_queue* mqueue, char* msg, int orig_fd) {
    struct msgc* new_msgc = malloc(sizeof(*new_msg));
    char* msg_str = malloc(256);
    strcpy(msg_str, msg);
    new_msgc->msg = msg_str;
    new_msgc->orig_fd = orig_fd;
    if (mqueue->size == 0) {
        mqueue->head = new_msgc;
    }
    else {    
        mqueue->tail->next = new_msgc;
        mqueue->tail = mqueue->tail->next;
    }
    mqueue->size += 1;
}

struct msgc* peek(struct msg_queue* mqueue) {
    return mqueue->head;
}

char* pop(struct msg_queue* mqueue) {
    if (mqueue->size == 0) {
        return "";
    }

    struct msgc* temp = mqueue->head;
    mqueue->head = mqueue->head->next;
    char* msg = temp->msg;
    free(temp);
    mqueue->size -= 1;
    return msg;
}
