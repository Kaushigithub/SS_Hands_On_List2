/*
============================================================================
Name : 14.c
Author : Kaushal Pancholi
Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on the monitor.
Date: 15 Sep, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{

	int pipefd[2];

	// opening of pipe using pipe(a)
	char buff[10];
	if (pipe(pipefd) == -1)
	{
		perror("Error in creating the pipe.\n"); // error in pipe
		exit(1); // exit from the program
	}

	write(pipefd[1], "Hello!", 7);
	printf("\n");

	read(pipefd[0], buff, 7);
	printf("%s \n", buff);
	return 0;
}

