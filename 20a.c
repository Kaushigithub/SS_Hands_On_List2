/*
============================================================================
Name : 20a.c
Author : Kaushal Pancholi
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 3 Oct, 2023.
============================================================================
*/

//Writer
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
int main()
{
    mkfifo("fifo_one", 0777);
    int fd = open("fifo_one", O_WRONLY);
    char data[] = "Hello! My name is Kaushal.\n";
    write(fd, data, sizeof(data));
    printf("Message sent by the Writer: %s\n", data);
    close(fd);
    return 0;
}

