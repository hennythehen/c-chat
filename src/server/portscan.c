#include "tcpserver.h" 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    int port = atoi(argv[1]);
    server_run(port);
}
