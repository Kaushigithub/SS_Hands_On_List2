/*
============================================================================
Name : 32a.c
Author : Kaushal Pancholi
Description : Write a program to implement semaphore to protect any critical section.
a. rewrite the ticket number creation program using semaphore
b. protect shared memory from concurrent write access
c. protect multiple pseudo resources ( may be two) using counting semaphore
d. remove the created semaphore
Date: 10 Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_TICKETS 100
int t_count = 0;

// Declare a semaphore
sem_t ticket_semaphore;

void* generate_ticket(void* arg) {
    int* thread_id = (int*)arg;

    for (int i = 0; i < 7; i++) {
        // Wait until the semaphore is available
        sem_wait(&ticket_semaphore);

        // Generate and print a ticket number
        printf("Thread %d generated ticket #%d\n", *thread_id, t_count);
        t_count++;

        // Release the semaphore
        sem_post(&ticket_semaphore);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[3]; // Create 3 threads
    int thread_ids[3] = {1, 2, 3};

    // Initialize the semaphore
    sem_init(&ticket_semaphore, 0, 1); // Initial value of 1

    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, generate_ticket, &thread_ids[i]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the semaphore
    sem_destroy(&ticket_semaphore);

    return 0;
}

