//
// Created by 姚双喜 on 9/13/16.
//

#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include "print.h"

int main() {

    // create socket
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        println("Create socket error: %s", strerror(errno));
        exit(1);
    }

    // connect socket
    struct sockaddr_in remote_addr;
    remote_addr.sin_family = AF_INET;
    remote_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    remote_addr.sin_port = htons(1500);
    if (connect(sock_fd, (struct sockaddr *) &remote_addr, sizeof(remote_addr))) {
        println("Connect socket error: %s", strerror(errno));
        exit(1);
    }

    size_t buffer_size = 1024;
    char buffer[buffer_size];
    while (1) {
        // receive message
        ssize_t ret = recv(sock_fd, buffer, buffer_size, 0);
        if (ret > 0) {
            buffer[ret] = 0x00;
            printf("%sConnected> ", buffer);
        } else {
            break;
        }
        // send message
        scanf("%s", buffer);
        send(sock_fd, buffer, buffer_size, 0);
    }

}