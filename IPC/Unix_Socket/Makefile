CC = gcc
CFLAGS = -Wall

all: client server

server: server.c common.h
	$(CC) $(CFLAGS) -o server server.c

client: client.c common.h
	$(CC) $(CFLAGS) -o client client.c

clean:
	rm -f server client