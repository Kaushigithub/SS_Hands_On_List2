/*
============================================================================
Name : 21b.c
Author : Kaushal Pancholi
Description : Write two programs so that both can communicate by FIFO -Use two way communication.
Date: 3 Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
   
    char message[100];

    // Open the FIFO for reading
    int fd = open("my_fifo", O_RDONLY);
    if (fd == -1) {
        perror("Error opening FIFO for reading");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for messages from the writer program...\n");

    while (1) {
        // Read data from the FIFO
        ssize_t bytes_read = read(fd, message, sizeof(message));

        if (bytes_read == 0) {
            printf("Writer has closed the FIFO. Exiting.\n");
            break;
        } else if (bytes_read > 0) {
            printf("Received message: %s\n", message);
        }
    }

    // Close the FIFO and exit
    close(fd);
    return 0;
}

