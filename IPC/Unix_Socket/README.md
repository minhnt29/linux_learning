# Unix Domain Sockets IPC Example

This repository demonstrates Inter-Process Communication (IPC) using Unix Domain Sockets in C. Unix Domain Sockets provide a mechanism for processes running on the same system to communicate with each other.

## What are Unix Domain Sockets?

Unix Domain Sockets are a form of IPC that allows processes to communicate with each other on the same system. They are similar to TCP/IP sockets but operate entirely within the operating system kernel and don't require network protocols.

### Key Features:
- Faster than network sockets (no network overhead)
- Secure (only processes on the same system can communicate)
- Support both stream (SOCK_STREAM) and datagram (SOCK_DGRAM) communication
- Can use file system permissions for access control

## Project Structure

```
.
├── README.md
├── server.c      # Server implementation
├── client.c      # Client implementation
└── common.h      # Common definitions and utilities
```

## Building and Running

To compile the examples:
```bash
gcc -o server server.c
gcc -o client client.c
```

To run the server:
```bash
./server
```

To run the client:
```bash
./client
```

## Implementation Details

The example demonstrates:
1. Creating a Unix Domain Socket
2. Binding the socket to a path
3. Server listening for connections
4. Client connecting to the server
5. Bidirectional communication
6. Proper cleanup and error handling

## Socket Types

1. **SOCK_STREAM**: Connection-oriented, reliable, two-way communication
2. **SOCK_DGRAM**: Connectionless, unreliable, message-based communication

## Best Practices

1. Always check return values from socket operations
2. Clean up socket files after use
3. Handle signals properly (especially SIGINT)
4. Use proper error handling
5. Implement proper shutdown procedures

## Common Use Cases

- Local service communication
- Database connections
- System daemons
- Process coordination
- Local IPC in containerized environments 