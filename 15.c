/*
============================================================================
Name : 15.c
Author : Kaushal Pancholi
Description : Write a simple program to send some data from parent to the child process.
Date: 15 Sep, 2023.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int pipe_fd[2];  // File descriptors for the pipe
    int pid;
    char data[] = "Hello! My name is Kaushal.\n";

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("Error in creating the pipe.\n");
        exit(EXIT_FAILURE);
    }

    // Create a child process
    pid = fork();

    if (pid == -1) {
        perror("Error in creating the child process.\n");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        close(pipe_fd[1]);  // Close the write end since the child only reads

        char buff[100];
        int r_bytes = read(pipe_fd[0], buff, sizeof(buff));

        if (r_bytes == -1) {
            perror("Error doing read.\n");
            exit(EXIT_FAILURE);
        }

        printf("Data received by the child: %s\n", buff);

        close(pipe_fd[0]);  // Close the read end in the child
    } 
    else 
    {
        // Parent process
        close(pipe_fd[0]);  // Close the read end since the parent only writes

        int w_bytes = write(pipe_fd[1], data, strlen(data));

        if (w_bytes == -1) {
            perror("Error doing write write.\n");
            exit(EXIT_FAILURE);
        }

        printf("Data sent by the parent: %s\n", data);

        close(pipe_fd[1]);  // Close the write end in the parent
    }

    return 0;
}


