/*
============================================================================
Name : 17b.c
Author : Kaushal Pancholi
Description : 17. Write a program to execute ls -l | wc.
	          b. use dup2
Date: 1 Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipe_fd[2]; // File descriptors for the pipe

    if (pipe(pipe_fd) == -1) {
        perror("Error in creating the pipe.\n");
        exit(EXIT_FAILURE);
    }

    int pid = fork();

    if (pid == -1) {
        perror("Error in creating the child preocess.");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
	close(pipe_fd[0]); // Close the read end of the pipe

        // Redirect the standard output (stdout) to write to the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]); // Close the write end of the pipe

        // Execute 'ls -l' command
        execlp("ls", "ls", "-l", (char *)NULL);

        // execlp() will only return if there's an error
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        close(pipe_fd[1]); // Close the read end of the pipe

        // Redirect the standard output (stdout) to write to the pipe
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]); // Close the write end of the pipe

        // Execute 'ls -l' command
        execlp("ls", "ls", "-l", (char *)NULL);

        // execlp() will only return if there's an error
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    return 0;
}

