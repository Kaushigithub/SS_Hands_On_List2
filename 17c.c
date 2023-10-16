/*
============================================================================
Name : 17c.c
Author : Kaushal Pancholi
Description : 17. Write a program to execute ls -l | wc.
                  c. use fcntl
Date: 1 Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2]; // File descriptors for the pipe

    if (pipe(pipe_fd) == -1) {
        perror("Error in creating pipe.");
        exit(EXIT_FAILURE);
    }

    int pid = fork();

    if (pid == -1) {
        perror("Error in creating the child process.");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        close(pipe_fd[0]);

        int flags = fcntl(pipe_fd[1], F_GETFD);
        //flags &= ~FD_CLOEXEC; // Clear the FD_CLOEXEC flag
        fcntl(pipe_fd[1], F_SETFD, flags);
        //if (pipe_fd[1] != STDOUT_FILENO) {
          //  dup2(pipe_fd[1], STDOUT_FILENO);
            //close(pipe_fd[1]);
        //}


        execlp("ls", "ls","-l", (char *)NULL);

        // execlp() will only return if there's an error
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        close(pipe_fd[1]);
        int flags = fcntl(pipe_fd[0], F_GETFD);
        //flags &= ~FD_CLOEXEC; // Clear the FD_CLOEXEC flag
        fcntl(pipe_fd[0], F_SETFD, flags);
       // if (pipe_fd[0] != STDIN_FILENO) {
         //   dup2(pipe_fd[0], STDIN_FILENO);
           // close(pipe_fd[0]);
        //}

        execlp("wc", "wc", (char *)NULL);

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
