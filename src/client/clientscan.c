#include "tcpclient.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    char* ipaddr = argv[1];
    int minport = atoi(argv[2]);
    int maxport = atoi(argv[3]);

    int port;
    for (port = minport; port <= maxport; port++) {
        if (fork() == 0) {
            serv_connect(ipaddr, port);
        }
    }

    while (wait(NULL) < 0) {}
}
