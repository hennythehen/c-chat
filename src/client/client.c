#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int serv_connect(char* ipaddr, int port)
{
    int sockfd;
    struct sockaddr_in host_addr_in;

    //create host address information
    host_addr_in.sin_family = AF_INET;
    host_addr_in.sin_port = htons(port);

    if (inet_aton(ipaddr, &host_addr_in.sin_addr) < 0) {
        perror("inet_aton"); exit(-1);
    }

    //create socket to connec to host
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
	    printf("socket failed\n"); exit(-1);
    }

    int addrlen = sizeof(host_addr_in);
    //attempt to connect to the host socket
    if (connect(sockfd,
                (struct sockaddr *) &host_addr_in,
                addrlen) < 0) {
        perror("connect"); exit(-1);
    }

    //child process listens for messages from server and prints them
    if (fork() == 0) {
        char rmsg[256];
        while(1) {
            read(sockfd, &rmsg, 256);
            printf("Someone said: %s\n", rmsg);
        }
    }

    char msg[256];
    while (1) {
        memset(&msg, 0, sizeof(msg));
        scanf("%s", msg);
        write(sockfd, &msg, 256);
    }
}
