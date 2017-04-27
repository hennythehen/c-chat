#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include "tcpserver.h"

void serv_listen(int port)
{
    int sockfd;

    //set up listening socket information
    struct sockaddr_in host_addr_in;
    memset(&host_addr_in, 0, sizeof(host_addr_in));
    host_addr_in.sin_family = AF_INET;
    host_addr_in.sin_port = htons(port);
    host_addr_in.sin_addr.s_addr = INADDR_ANY;


    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
	    printf("socket failed\n"); exit(-1);
    }
    printf("%d\n", sockfd);
    int bind_result;
    if (bind_result = (bind(sockfd,
                (struct sockaddr *) &host_addr_in,
                sizeof(host_addr_in))) == -1) {
        printf("bind failed\n"); perror("bind"); exit(-1);
    }

    listen(sockfd, 1);

    printf("Listening on port %d\n", ntohs(host_addr_in.sin_port));

    struct sockaddr_in peer_saddr;
    //set all data in peer_saddr to NULL
    memset(&peer_saddr, 0, sizeof(peer_saddr));
    int socklen = sizeof(peer_saddr);
    int accept_fd = accept(sockfd, 
            (struct sockaddr *) &peer_saddr, 
            &socklen);
    if (accept_fd == -1) {
        perror("accept"); exit(-1);
    }

    printf("port %d accepted\n", port);


}
