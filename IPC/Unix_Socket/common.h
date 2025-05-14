#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

#define SOCKET_PATH "/tmp/unix_socket_example"
#define BUFFER_SIZE 1024

// Error handling macro
#define ERROR_EXIT(msg) do { \
    perror(msg); \
    exit(EXIT_FAILURE); \
} while(0)

// Function to create a Unix domain socket
int create_unix_socket(void) {
    int sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock_fd == -1) {
        ERROR_EXIT("socket");
    }
    return sock_fd;
}

// Function to set up socket address structure
void setup_sockaddr(struct sockaddr_un *addr) {
    memset(addr, 0, sizeof(struct sockaddr_un));
    addr->sun_family = AF_UNIX;
    strncpy(addr->sun_path, SOCKET_PATH, sizeof(addr->sun_path) - 1);
}

#endif // COMMON_H 