#ifndef MSGQUEUE_H 
#define MSGQUEUE_H

struct msg_queue {
    struct msgc* head;
    struct msgc* tail;
    int size;
};

struct msgc {
    char* msg;
    struct msgc* next;
    int orig_fd;
};

void new_msg(struct msg_queue*, char*, int);

struct msgc* peek(struct msg_queue*);
char* pop(struct msg_queue*);
#endif
