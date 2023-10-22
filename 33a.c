/*
============================================================================
Name : 33a.c
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
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_length = sizeof(client_address);

    // Create socket
    printf("Creating a socket\n");
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error creating server socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12345); // Port number -  conversion from host byte order to network byte order
    server_address.sin_addr.s_addr = INADDR_ANY; // Listen on all available network interfaces

    // Bind the socket to the server address
    printf("Binding the socket\n");
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Error binding");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    printf("Listening for incoming connections\n");
    if (listen(server_socket, 5) == -1) {
        perror("Error listening");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port 12345...\n");

    // Accept incoming connection
    client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_length);
    if (client_socket == -1) {
        perror("Error accepting connection");
        exit(EXIT_FAILURE);
    }

    printf("Accepted connection from %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

    // Receive data from the client
    char buffer[1024];
    ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received == -1) {
        perror("Error receiving data");
exit(EXIT_FAILURE);
    }

    buffer[bytes_received] = '\0';
    printf("Received data from client: %s\n", buffer);

    // Send a response back to the client
    const char* response = "Hello from the server!";
    ssize_t bytes_sent = send(client_socket, response, strlen(response), 0);
    if (bytes_sent == -1) {
        perror("Error sending data");
        exit(EXIT_FAILURE);
    }

    // Close sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
