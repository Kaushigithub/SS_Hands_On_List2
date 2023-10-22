/*
============================================================================
Name : 17a.c
Author : Kaushal Pancholi
Description : Write a program to execute ls -l | wc.
	      a. use dup
Date: 1 Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>
int main() {
    int pipe_fd[2]; // File descriptors for the pipe

    if (pipe(pipe_fd) == -1) {
        perror("Error in creating the pipe.\n");
        exit(EXIT_FAILURE);
    }

    int pid = fork();

    if (pid == -1) {
        perror("Error in creating the child process.\n");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        close(pipe_fd[0]);
       close(1);	
        dup(pipe_fd[1]);
        close(pipe_fd[1]);

        // Execute 'ls -l' command
        execlp("ls", "ls","-l",NULL);

        // execlp() will only return if there's an error
        perror("execlp");
        exit(EXIT_FAILURE);
    } 
    else{
        // Parent process
        close(pipe_fd[1]); 
	close(0);
        dup(pipe_fd[0]);
        close(pipe_fd[0]);

        execlp("wc", "wc",NULL);

        // execlp() will only return if there's an error
        perror("execlp");
        exit(EXIT_FAILURE);
    }
   close(pipe_fd[0]);
   close(pipe_fd[1]);
   wait(NULL);
  wait(NULL);

    return 0;
}
