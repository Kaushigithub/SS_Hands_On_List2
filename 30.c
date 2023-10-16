/*
============================================================================
Name : 30.c
Author : Kaushal Pancholi
Description : Write a program to create a shared memory.
a. write some data to the shared memory
b. attach with O_RDONLY and check whether you are able to overwrite.
c. detach the shared memory
d. remove the shared memory
Date: 10 Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

int main() {
    //Create a key for the shared memory segment
    key_t key = ftok("/tmp", 'K');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    printf("Creating a shared memory segment of size 128 bytes\n");
    int shmid = shmget(key, 128, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    printf("Attaching the shared memory segment for writing\n");
    char *shared_memory = shmat(shmid, NULL, 0);
    if (shared_memory == (char *)(-1)) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    printf("Writing data to the shared memory\n");
    strcpy(shared_memory, "Hello, Shared Memory!");

    printf("Detaching the shared memory\n");
    if (shmdt(shared_memory) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    printf("Reattaching the shared memory as read-only (O_RDONLY)\n");
    char *readonly_memory = shmat(shmid, NULL, SHM_RDONLY);
    if (readonly_memory == (char *)(-1)) {
        perror("shmat (O_RDONLY)");
        exit(EXIT_FAILURE);
    }

    printf("Attempting to overwrite the read-only shared memory (this will fail)\n");
    //strcpy(readonly_memory, "This won't work!");
    //this will give segmentation fault core dumped
    printf("Detaching the read-only shared memory\n");
    if (shmdt(readonly_memory) == -1) {
        perror("shmdt (O_RDONLY)");
        exit(EXIT_FAILURE);
    }
   // else {
        //printf("Trying to overwrite data in O_RDONLY mode...\n");
        // This should result in a segmentation fault because we cannot write in O_RDONLY mode
       // strcpy(readonly_memory, "Attempt to overwrite");
    //}

    printf("Removing the shared memory segment\n");
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl IPC_RMID");
        exit(EXIT_FAILURE);
    }

    printf("Shared memory removed.\n");

    return 0;
}
