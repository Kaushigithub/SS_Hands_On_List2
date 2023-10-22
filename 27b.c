/*
============================================================================
Name : 27b.c
Author : Kaushal Pancholi
Description : Write a program to receive messages from the message queue.
b. with IPC_NOWAIT as a flag
Date: 9 Oct, 2023.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
struct msg_buffer {
    long msg_type;
    char msg_text[512];
};
int main() {

    key_t key = ftok(".", 'A');
    int msgqid;
    struct msg_buffer msg;

    // Create or obtain a message queue with the specified key
    msgqid = msgget(key, 0666 | IPC_CREAT);

    // Receiving a message with flag value 0 (blocking)
    if (msgrcv(msgqid, &msg, sizeof(msg.msg_text), 1, IPC_NOWAIT) == -1) {
        perror("msgrcv");
        return 1;
    }

    printf("Received message: %s\n", msg.msg_text);

    return 0;
}

