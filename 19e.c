/*
============================================================================
Name : 19e.c
Author : Kaushal Pancholi
Description : Create a FIFO file by
e. mkfifo system call
Date: 2 Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    if (mkfifo("mkfifo_fifo", 0666) == -1) {
        perror("fifo");
        exit(EXIT_FAILURE);
    }

    return 0;
}

// Create a FIFO using mkfifo - mkfifo mkfifo_myfifo 
// Using strace with mkfifo - strace -o mkfifo_strace.log mkfifo mkfifo_myfifo 

