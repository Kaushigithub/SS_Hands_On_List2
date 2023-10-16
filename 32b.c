/*
============================================================================
Name : 32b.c
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

#define SHARED_MEMORY_SIZE 7

int shared_memory[SHARED_MEMORY_SIZE];
sem_t semaphore;

void* write_to_shared_memory(void* arg) {
    int* data = (int*)arg;
    for (int i = 0; i < SHARED_MEMORY_SIZE; i++) {
        sem_wait(&semaphore); // Wait until the semaphore is available

        shared_memory[i] = *data;
        printf("Thread wrote %d to shared memory at index %d\n", *data, i);

        sem_post(&semaphore); // Release the semaphore
    }
    pthread_exit(NULL);
}

int main() {
    int data_to_write = 52;

    pthread_t thread1, thread2;

    // Initialize the semaphore
    sem_init(&semaphore, 0, 1); // Initial value of 1

    pthread_create(&thread1, NULL, write_to_shared_memory, &data_to_write);
    pthread_create(&thread2, NULL, write_to_shared_memory, &data_to_write);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy the semaphore
    sem_destroy(&semaphore);

    return 0;
}
