/*
============================================================================
Name : 19d.c
Author : Kaushal Pancholi
Description : Create a FIFO file by
d. mknod system call
Date: 2 Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    if (mknod("mknod_myfifo", S_IFIFO | 0666, 0) == -1) {
        perror("mknod");
        exit(EXIT_FAILURE);
    }

    return 0;
}

// Create a FIFO using mknod - sudo mknod mknod_myfifo p
// Using strace with mknod - sudo strace -o mknod_strace.log mknod mknod_myfifo p


