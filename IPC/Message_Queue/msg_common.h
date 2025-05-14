#ifndef MSG_COMMON_H
#define MSG_COMMON_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MSG_KEY 1234
#define MSG_TYPE 1
#define MAX_MSG_SIZE 256

// Message structure
struct message {
    long mtype;
    char mtext[MAX_MSG_SIZE];
};

#endif 