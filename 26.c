/*
============================================================================
Name : 26.c
Author : Kaushal Pancholi
Description : Write a program to send messages to the message queue. Check $ipcs -q
Date: 9 Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer 
{
    long msg_type;
    char msg_text[512];
};
int main() 
{
    key_t key;
    int msgid;
    struct msg_buffer message;
    key = ftok(".", 'B');
    msgid = msgget(key, 0666);
    message.msg_type = 1;
    printf("Enter a message to send to the message queue:\n");
    fgets(message.msg_text, 512, stdin);
    size_t len = strlen(message.msg_text);
    if (len > 0 && message.msg_text[len - 1] == '\n') 
    {
        message.msg_text[len - 1] = '\0';
    }
    msgsnd(msgid, (void*)&message, 512, 0);
    printf("Message sent to the message queue.\n");
    return 0;
}

