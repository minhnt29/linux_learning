#include "msg_common.h"

int main() {
    int msgid;
    struct message msg;
    char input[MAX_MSG_SIZE];

    // Create or access message queue
    msgid = msgget(MSG_KEY, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    printf("Writer: Message queue created/accessed successfully\n");
    printf("Writer: Enter messages (type 'quit' to exit):\n");

    while (1) {
        // Get message from user
        printf("Writer: Enter message: ");
        if (fgets(input, MAX_MSG_SIZE, stdin) == NULL) {
            break;
        }

        // Remove newline character
        input[strcspn(input, "\n")] = 0;

        // Check for quit command
        if (strcmp(input, "quit") == 0) {
            break;
        }

        // Prepare message
        msg.mtype = MSG_TYPE;
        strncpy(msg.mtext, input, MAX_MSG_SIZE - 1);
        msg.mtext[MAX_MSG_SIZE - 1] = '\0';

        // Send message
        if (msgsnd(msgid, &msg, strlen(msg.mtext) + 1, 0) == -1) {
            perror("msgsnd failed");
            exit(1);
        }

        printf("Writer: Message sent successfully\n");
    }

    // Send termination message
    msg.mtype = MSG_TYPE;
    strcpy(msg.mtext, "quit");
    msgsnd(msgid, &msg, strlen(msg.mtext) + 1, 0);

    printf("Writer: Exiting...\n");
    return 0;
} 