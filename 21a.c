/*
============================================================================
Name : 21a.c
Author : Kaushal Pancholi
Description : Write two programs so that both can communicate by FIFO -Use two way communication.
Date: 3 Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {

    char message[100];

    // Open the FIFO for writing
    int fd = open("my_fifo", O_WRONLY);
    if (fd == -1) {
        perror("Error opening FIFO for writing");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Read user input
        printf("Enter a message to send (or 'quit' to exit): ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0'; // Remove the newline character

        if (strcmp(message, "quit") == 0) {
            break; // Exit the loop if the user enters 'quit'
        }

        // Write the message to the FIFO
        write(fd, message, strlen(message) + 1); // Include the null terminator
    }

    // Close the FIFO and exit
    close(fd);
    return 0;
}

