/*
============================================================================
Name : 28.c
Author : Kaushal Pancholi
Description : Write a program to change the exiting message queue permission. (use msqid_ds structure)
Date: 9 Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int main() {
    key_t key;
    int msgid;
    key = ftok(".", 'B');
    msgid = msgget(key, 0666);
    struct msqid_ds msq_info;
    msgctl(msgid, IPC_STAT, &msq_info);
    printf("Original Permission: %#o\n", msq_info.msg_perm.mode);
    msq_info.msg_perm.mode=0664;
    msgctl(msgid, IPC_SET, &msq_info);
    printf("Updated Permission: %#o\n", msq_info.msg_perm.mode);
    return 0;
}
