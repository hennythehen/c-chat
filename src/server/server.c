#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "tcpserver.h"
#include "msgqueue.h"
#include "pipesem.h"
#include "clientlist.h"

int server_run(int port)
{
    int sockfd = 0;
    //set up listening socket information
    struct sockaddr_in host_addr_in;
    host_addr_in.sin_family = AF_INET;
    host_addr_in.sin_port = htons(port);
    host_addr_in.sin_addr.s_addr = INADDR_ANY;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        return -1;
    }
    if (bind(sockfd,
                (struct sockaddr *) &host_addr_in,
                sizeof(host_addr_in)) == -1) {
        return -1;
    }

    int con_queue_max = 20;
    listen(sockfd, con_queue_max);
    
    //Initialize dynamic list of clients
    int max_cl_list_size = sizeof(struct client_list) +
        (sizeof(struct msgc) * con_queue_max);
    struct client_list* cl_list = malloc(max_cl_list_size);

    //Initialize dynamic message storage 
    int msg_queue_max = 50;
    int msg_queue_size = (sizeof(struct msg_queue) + 
        sizeof(struct msgc) * msg_queue_max);
    struct msg_queue* msg_queue = malloc(msg_queue_size);
    int msg_queue_mutex[2];
    pipe(msg_queue_mutex);
    signal(msg_queue_mutex); 

    //Create semaphore to track messages waiting to be posted
    int msg_lock_fd[2];
    pipe(msg_lock_fd);

    /*
     * child process waits for messages to arrive
     * and propogates them to connected clients
     */
    if (fork() == 0) {
        while(1) {
            wait(msg_lock_fd);
            if (peek(msg_queue) == NULL) {
                continue;
            }

            post_msg(cl_list, msg_queue);
        }
    }

    /*
     * Listening loop. Accepts new connections and creates
     * a child process to handle the connection
     */
    while(1) {
        struct sockaddr_in peer_saddr;
        memset(&peer_saddr, 0, sizeof(peer_saddr));
        int socklen = sizeof(peer_saddr);
        
        int client_fd;
        client_fd = accept(sockfd,
                (struct sockaddr *) &peer_saddr,
                &socklen); 
        struct tcp_client* client = malloc(sizeof(client));
        client->cl_sockaddr = &peer_saddr;
        client->open_fd = client_fd;
        push_client(cl_list, client);

        if (fork() == 0) {
            while(1) {
                char readbuff[256];
                read(client_fd, readbuff, 256);
                new_msg(msg_queue, readbuff, client_fd);
                signal(msg_lock_fd);
            }
        }
    }

    free(msg_queue);
    free(cl_list);
}
/*
void child_listen(struct msg_queue* msgs,

        int sockfd,
        struct sockaddr_in* peer_saddr,
        int* size)
{
    int accept_fd;
    accept_fd = accept(sockfd,
            (struct sockaddr *) peer_saddr,
            size);
    char buffer[256];
    read(accept_fd
*/
