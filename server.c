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
#include "print.h"

int main() {

    int port = 1500;

    // create socket
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        println("Create socket error.");
        exit(1);
    }

    // bind
    struct sockaddr_in local_addr;
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = htons(INADDR_ANY);
    local_addr.sin_port = htons(port);
    if (bind(sock_fd, (struct sockaddr *) &local_addr, sizeof(local_addr)) < 0) {
        println("Bind socket error: %s", strerror(errno));
        exit(1);
    }

    // listen
    if (listen(sock_fd, 5) < 0) {
        println("Listen socket error: %s", strerror(errno));
        exit(1);
    }

    println("Server started and waiting connection...");

    // accept
    struct sockaddr_in remote_addr;
    socklen_t address_len = sizeof(remote_addr);
    while (1) {
        int accepted_fd = accept(sock_fd, (struct sockaddr *) &remote_addr, &address_len);
        if (accepted_fd < 0) {
            println("Accept socket error: %s", strerror(errno));
            break;
        }
        println("Accepted connection: %s",  inet_ntoa(remote_addr.sin_addr));
        // receive
        size_t size = 1024;
        char buffer[size];
        while (1) {
            if (send(accepted_fd, "RECEIVED\n", 10, 0) < 0) {
                println("Send message error: %s", strerror(errno));
            }
            ssize_t recv_len = recv(accepted_fd, buffer, size, 0);
            if (recv_len <= 0) {
                break;
            }
            if (buffer[recv_len - 1] == '\n') {
                buffer[recv_len - 1] = 0x00;
            } else {
                buffer[recv_len] = 0x00;
            }
            println("%s says: %s", inet_ntoa(remote_addr.sin_addr), buffer);
        }
    }
}