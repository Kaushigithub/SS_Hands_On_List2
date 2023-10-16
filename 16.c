/*
============================================================================
Name : 16.c
Author : Kaushal Pancholi
Description : Write a program to send and receive data from parent to child vice versa. Use two way communication.
Date: 1 Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipe1[2];  // Pipe for parent to child communication
    int pipe2[2];  // Pipe for child to parent communication
    int pid;

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Error in creating the pipe.\n");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("Eroor in creating the child process.\n");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        close(pipe1[1]);  // Close the write end from parent to child
        close(pipe2[0]);  // Close the read end from child to parent

        char data_from_parent[100];
        int r_bytes = read(pipe1[0], data_from_parent, sizeof(data_from_parent));

        if (r_bytes == -1) {
            perror("error in read.\n");
            exit(EXIT_FAILURE);
        }

        printf("Child received from parent: %s\n", data_from_parent);

        // Send a response from child to parent
        char data[] = "Hello parent!";
        int w_bytes = write(pipe2[1], data, strlen(data));

        if (w_bytes == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        close(pipe1[0]);  // Close the read end in the child
        close(pipe2[1]);  // Close the write end in the child
    } else {
        // Parent process
        close(pipe1[0]);  // Close the read end from parent to child
        close(pipe2[1]);  // Close the write end from child to parent

        char data_to_child[] = "Hello child!";
        int w_bytes = write(pipe1[1], data_to_child, strlen(data_to_child));

        if (w_bytes == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        // Wait for a response from the child
        char data_from_child[100];
        int r_bytes = read(pipe2[0], data_from_child, sizeof(data_from_child));

        if (r_bytes == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        printf("Parent received from child: %s\n", data_from_child);

        close(pipe1[1]);  // Close the write end in the parent
        close(pipe2[0]);  // Close the read end in the parent
    }

    return 0;
}
