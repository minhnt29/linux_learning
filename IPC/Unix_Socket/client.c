#include "common.h"

int main(void) {
    int sock_fd;
    struct sockaddr_un addr;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    // Create socket
    sock_fd = create_unix_socket();

    // Set up address structure
    setup_sockaddr(&addr);

    // Connect to server
    if (connect(sock_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        ERROR_EXIT("connect");
    }

    printf("Connected to server\n");

    // Send messages to server
    while (1) {
        printf("Enter message (or 'quit' to exit): ");
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            break;
        }

        // Send message to server
        if (send(sock_fd, buffer, strlen(buffer), 0) == -1) {
            ERROR_EXIT("send");
        }

        // Check if user wants to quit
        if (strncmp(buffer, "quit", 4) == 0) {
            break;
        }

        // Receive response from server
        bytes_read = recv(sock_fd, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_read <= 0) {
            if (bytes_read == 0) {
                printf("Server closed connection\n");
            } else {
                ERROR_EXIT("recv");
            }
            break;
        }

        buffer[bytes_read] = '\0';
        printf("Server response: %s", buffer);
    }

    close(sock_fd);
    return EXIT_SUCCESS;
} 