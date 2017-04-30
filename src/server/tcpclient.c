#include "tcpclient.h"
#include <unistd.h>

void write_msg(struct tcp_client* tcp_cl, char* msg) {
    write(tcp_cl->open_fd, msg, 256);
}
