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

	int fd = fcntl(1, F_DUPFD, 0);   // duplicating the standard output
       fcntl(1, F_SETFD, FD_CLOEXEC);
       close(1);  // closing stdout
        fcntl(pipe_fd[1], F_DUPFD, 1);   // duplicating the write end of the pipe to the stdout i.e. redirecting the stdout to the write end of the pipe
    

        execlp("ls", "ls","-l", NULL);

        // execlp() will only return if there's an error
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        close(pipe_fd[1]);

	// Redirect stdin to the read end of the pipe using fcntl
        int fd = fcntl(0, F_DUPFD, 0);
        fcntl(0, F_SETFD, FD_CLOEXEC);
	close(0);
        fcntl(pipe_fd[0], F_DUPFD, 0);
        execlp("wc", "wc", NULL);

        // execlp() will only return if there's an error
        perror("execlp");
        exit(EXIT_FAILURE);
    }
	
   close(pipe_fd[0]);
   close(pipe_fd[1]);

    //wait(NULL);
   // wait(NULL);
    return 0;
}
