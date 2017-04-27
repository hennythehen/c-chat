#include "tcpserver.h" 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    int minport = atoi(argv[1]);
    int maxport = atoi(argv[2]);

    int port;
    for (port = minport; port <= maxport; port++) {
        if (fork() == 0) {
            serv_listen(port);
        }
    }

    while (wait(NULL) > 0) {}

    printf("Done");
}
