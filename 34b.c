/*
============================================================================
Name : 34b.c
Author : Kaushal Pancholi
Description : Write a program to create a concurrent server.
b. use pthread_create
Date: 11 Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>

#define PORT 12345
#define MAX_CONNECTIONS 5

void *handle_client(void *client_socket_ptr) {
    int client_socket = *(int *)client_socket_ptr;
    char buffer[256];
    int n;

    while (1) {
        n = read(client_socket, buffer, sizeof(buffer));
        if (n <= 0) {
            close(client_socket);
            pthread_exit(NULL);
        }
        buffer[n] = '\0';
        printf("Received: %s", buffer);
        write(client_socket, "Message received\n", 17);
    }
}

//void sigint_handler(int sig) {
  //  printf("CTRL+C pressed. Server shutting down...\n");
    //exit(0);
//}

int main() {
  //  signal(SIGINT, sigint_handler); // Register the SIGINT signal handler

    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error in socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error in bind");
        exit(1);
    }

    if (listen(server_socket, MAX_CONNECTIONS) == -1) {
        perror("Error in listen");
        exit(1);
    }

    printf("Server is listening on port %d\n", PORT);

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
        if (client_socket == -1) {
            perror("Error in accept");
            continue;
        }

        pthread_t tid;
        if (pthread_create(&tid, NULL, handle_client, &client_socket) != 0) {
            perror("Error in pthread_create");
            close(client_socket);
        }
    }

    return 0;
}

