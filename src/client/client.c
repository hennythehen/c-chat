#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>

int serv_connect(char* ipaddr, int port)
{
    int sockfd;
    struct sockaddr_in host_addr_in;

    //create host address information
    host_addr_in.sin_family = AF_INET;
    host_addr_in.sin_port = htons(port);
    printf("%u\n", ntohs(host_addr_in.sin_port));

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
    printf("port %d connected\n", port);
}
