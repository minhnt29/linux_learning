#include "msg_common.h"

int main() {
    int msgid;
    struct message msg;

    // Access message queue
    msgid = msgget(MSG_KEY, 0666);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    printf("Receiver: Message queue accessed successfully\n");
    printf("Receiver: Waiting for messages...\n");

    while (1) {
        // Receive message
        if (msgrcv(msgid, &msg, MAX_MSG_SIZE, 1, 0) == -1) {
            perror("msgrcv failed");
            exit(1);
        }

        printf("Receiver: Received message: %s\n", msg.mtext);

        // Check for termination message
        if (strcmp(msg.mtext, "quit") == 0) {
            break;
        }
    }

    printf("Receiver: Exiting...\n");
    return 0;
} 