/*
============================================================================
Name : 20b.c
Author : Kaushal Pancholi
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 3 Oct, 2023.
============================================================================
*/


//Reader
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
int main()
{
    int fd = open("fifo_one", O_RDONLY);
    char buff[100];
    int rd_bytes = read(fd, buff, sizeof(buff));
    buff[rd_bytes] = '\0';
    printf("Reader received: %s\n",buff);
    close(fd);
    unlink("fifo_one");
    return 0;
}
