/*
============================================================================
Name : 33b.c
Author : Kaushal Pancholi
Description : Write a program to communicate between two machines using socket.
Date: 11 Oct, 2023.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int client_socket;
    struct sockaddr_in server_address;

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Error creating client socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12345); // Port number
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server.\n");

    // Send data to the server
    const char* message = "Hello from the client!";
    ssize_t bytes_sent = send(client_socket, message, strlen(message), 0);
    if (bytes_sent == -1) {
        perror("Error sending data");
        exit(EXIT_FAILURE);
    }

    // Receive a response from the server
    char buffer[1024];
    ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received == -1) {
        perror("Error receiving data");
        exit(EXIT_FAILURE);
    }

    buffer[bytes_received] = '\0';
    printf("Received response from server: %s\n", buffer);

    // Close the socket
    close(client_socket);
return 0;
}
