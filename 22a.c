/*
============================================================================
Name : 22a.c
Author : Kaushal Pancholi
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select system call with FIFO.
Date: 3 Oct, 2023.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include<string.h>

int main() {
    int fd;
    fd = open("fifo_22", O_WRONLY | O_CREAT);

    if (fd == -1) {
        perror("open");
        exit(1);
    }

    char message[] = "Hello, FIFO!";
    ssize_t bytes_written = write(fd, message, strlen(message));

    if (bytes_written > 0) {
        printf("Wrote message to FIFO: %s\n", message);
    } else {
        perror("write");
    }
    unlink("fifo_22");
    close(fd);
    return 0;
}

