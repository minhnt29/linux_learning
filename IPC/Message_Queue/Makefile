CC = gcc
CFLAGS = -Wall

all: writer receiver

writer: writer.c msg_common.h
	$(CC) $(CFLAGS) -o writer writer.c

receiver: receiver.c msg_common.h
	$(CC) $(CFLAGS) -o receiver receiver.c

clean:
	rm -f writer receiver 