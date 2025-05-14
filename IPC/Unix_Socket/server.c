#include "common.h"
#include <signal.h>

static int server_fd = -1;

void cleanup(void) {
    if (server_fd != -1) {
        close(server_fd);
    }
    unlink(SOCKET_PATH);
}

void signal_handler(int signum) {
    printf("\nReceived signal %d, cleaning up...\n", signum);
    cleanup();
    exit(EXIT_SUCCESS);
}

int main(void) {
    struct sockaddr_un addr;
    int client_fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    // Register signal handlers
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    // Create socket
    server_fd = create_unix_socket();

    // Set up address structure
    setup_sockaddr(&addr);

    // Remove existing socket file if it exists
    unlink(SOCKET_PATH);

    // Bind socket to address
    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        ERROR_EXIT("bind");
    }

    // Listen for connections
    if (listen(server_fd, 5) == -1) {
        ERROR_EXIT("listen");
    }

    printf("Server is listening on %s\n", SOCKET_PATH);

    while (1) {
        // Accept connection
        client_fd = accept(server_fd, NULL, NULL);
        if (client_fd == -1) {
            ERROR_EXIT("accept");
        }

        printf("Client connected\n");

        // Handle client communication
        while ((bytes_read = recv(client_fd, buffer, BUFFER_SIZE - 1, 0)) > 0) {
            buffer[bytes_read] = '\0';
            printf("Received: %s", buffer);

            // Echo back to client
            if (send(client_fd, buffer, bytes_read, 0) == -1) {
                ERROR_EXIT("send");
            }
        }

        if (bytes_read == -1) {
            ERROR_EXIT("recv");
        }

        close(client_fd);
        printf("Client disconnected\n");
    }

    cleanup();
    return EXIT_SUCCESS;
} 