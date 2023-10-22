/*
============================================================================
Name : 27a.c
Author : Kaushal Pancholi
Description : Write a program to receive messages from the message queue.
              a. with 0 as a flag
Date: 9 Oct, 2023.
============================================================================
*/


#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message {
    long mtype; // Message type
    char mtext[100]; // Message content
};

int main() {
    key_t key = ftok(".", 'A');
    int msgqid;
    struct message msg;

    // Create or obtain a message queue with the specified key
    msgqid = msgget(key, 0666 | IPC_CREAT);

    // Receiving a message with flag value 0 (blocking)
    if (msgrcv(msgqid, &msg, sizeof(msg.mtext), 1, 0) == -1) {
        perror("msgrcv");
        return 1;
    }

    printf("Received message: %s\n", msg.mtext);

    return 0;
}

