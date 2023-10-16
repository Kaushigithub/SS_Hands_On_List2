/*
============================================================================
Name : 18.c
Author : Kaushal Pancholi
Description : Write a program to find out total number of directories on the pwd.
execute ls -l | grep ^d | wc ? Use only dup2.
Date: 2 Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    int pid;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        // Close the read end of the pipe
        close(pipefd[0]);

        // Redirect standard output to the write end of the pipe
        dup2(pipefd[1], STDOUT_FILENO);

        // Execute the 'ls -l' command
        execlp("ls", "ls", "-l", (char *)NULL);

        // If execlp fails, print an error message
        perror("execlp");
        exit(EXIT_FAILURE);
    } else { // Parent process
        // Close the write end of the pipe
        close(pipefd[1]);

        // Redirect standard input to the read end of the pipe
        dup2(pipefd[0], STDIN_FILENO);

        // Create a pipe for wc -l
        int wc_pipefd[2];
        if (pipe(wc_pipefd) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        int wc_pid = fork();

        if (wc_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (wc_pid == 0) { // Child process for wc -l
            // Close the read end of the wc_pipe
            close(wc_pipefd[0]);

            // Redirect standard output to the write end of the wc_pipe
            dup2(wc_pipefd[1], STDOUT_FILENO);

            // Execute the 'grep ^d' command
            execlp("grep", "grep", "^d", (char *)NULL);

            // If execlp fails, print an error message
            perror("execlp");
            exit(EXIT_FAILURE);
        } else { // Parent process
            // Close the write end of the wc_pipe
            close(wc_pipefd[1]);

            // Redirect standard input to the read end of the wc_pipe
            dup2(wc_pipefd[0], STDIN_FILENO);

            // Execute the 'wc -l' command to count lines
            execlp("wc", "wc", "-l", (char *)NULL);

            // If execlp fails, print an error message
            perror("execlp");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
