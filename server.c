//
// Created by 姚双喜 on 9/12/16.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {

    int port = 1500;

    // create socket
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        printf("Create socket error.\n");
        exit(1);
    }

    // bind
    struct sockaddr_in local_addr;
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = htons(INADDR_ANY);
    local_addr.sin_port = htons(port);
    if (bind(sock_fd, (struct sockaddr *) &local_addr, sizeof(local_addr)) < 0) {
        printf("Bind socket error: %s\n", strerror(errno));
        exit(1);
    }

    // listen
    if (listen(sock_fd, 5) < 0) {
        printf("Listen socket error: %s\n", strerror(errno));
        exit(1);
    }

    printf("Started server success and waiting connection...\n");

    // accept
    struct sockaddr_in remote_addr;
    socklen_t address_len = sizeof(remote_addr);
    while (1) {
        int accepted_fd = accept(sock_fd, (struct sockaddr *) &remote_addr, &address_len);
        if (accepted_fd < 0) {
            printf("Accept socket error: %s\n", strerror(errno));
            break;
        }
        printf("Accepted connection: %s\n",  inet_ntoa(remote_addr.sin_addr));
        // receive
        int size = 256;
        char buffer[size];
        while (1) {
            int recv_len = recv(accepted_fd, buffer, size, 0);
            if (recv_len <= 0) {
                break;
            }
            buffer[recv_len] = 0x00;
            printf("%s", buffer);
            if (send(accepted_fd, "RECEIVED\n", 10, 0) < 0) {
                printf("Send message error: %s\n", strerror(errno));
            }
        }
    }
}