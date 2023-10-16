/*
============================================================================
Name : 22b.c
Author : Kaushal Pancholi
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select system call with FIFO.
Date: 3 Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>

int main() {
    int fd;
    fd_set readSet;
    struct timeval timeout;
    mkfifo("fifo_22", 0666);
    fd = open("fifo_22", O_RDWR);
    FD_ZERO(&readSet);
    FD_SET(fd, &readSet);
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;
    int selectResult = select(fd + 1, &readSet, NULL, NULL, &timeout);
    if(selectResult)
    {
        char buffer[100];
        int bytesRead = read(fd, buffer, sizeof(buffer));
        if(bytesRead > 0)
        {
            buffer[bytesRead] = '\0';  // Null-terminate the string
            printf("Received message: %s\n", buffer);
        }
        else
        {
            printf("Error reading data from FIFO.\n");
        }

    }
    else
    {
        printf("No data written within 10 seconds.\n");
    }
    char response[] = "Response from Reader!";
    write(fd, response, sizeof(response));
    close(fd);
    unlink("fifo_22");
    return 0;
}
