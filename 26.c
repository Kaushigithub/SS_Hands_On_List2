/*
============================================================================
Name : 26.c
Author : Kaushal Pancholi
Description : Write a program to send messages to the message queue. Check $ipcs -q
Date: 9 Oct, 2023.
============================================================================
*/


#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Define a message structure
struct message {
    long mtype;  // Message type (must be > 0)
    char mtext[100]; // Message content
};

int main() {
    key_t key = ftok(".", 'A'); // Generate a unique key
    int msgqid;
    struct message msg;

    // Create or obtain a message queue with the specified key
    msgqid = msgget(key, 0666 | IPC_CREAT);
    if (msgqid == -1) {
        perror("msgget");
        return 1;
    }

    // Send messages to the message queue
    msg.mtype = 1; // Message type (must be > 0)
    strcpy(msg.mtext, "Hello, this is a message!");
    if (msgsnd(msgqid, &msg, sizeof(msg.mtext), 0) == -1) {
        perror("msgsnd");
        return 1;
    }

    // Check the status of the message queue
   // system("ipcs -q");

    return 0;
}


