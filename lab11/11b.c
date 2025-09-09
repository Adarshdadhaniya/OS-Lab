/* Solution for producer-consumer problem using mutex and semaphore. 
   3 producers and 3 consumers are used to demonstrate the solution.
*/
// to compile:  gcc filename.c -pthread

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#define MaxItems 3       // Maximum items a producer can produce or a consumer can consume
#define BufferSize 3     // Size of the buffer

sem_t empty;             // Semaphore to count empty slots in buffer
sem_t full;              // Semaphore to count full slots in buffer
int in = 0;              // Index for producer to insert item
int out = 0;             // Index for consumer to remove item
int buffer[BufferSize];  // Shared buffer
pthread_mutex_t mutex;   // Mutex lock to protect buffer access

// Producer thread function
void *producer(void *pno)
{   
    int item;
    for(int i = 0; i < MaxItems; i++) {
        item = rand()%100; // Produce a random item

        sem_wait(&empty); // Decrement empty count; wait if buffer is full
        pthread_mutex_lock(&mutex); // Lock the buffer

        buffer[in] = item; // Insert item into buffer
        printf("Producer %d: Insert Item %d at %d\n", *((int *)pno), buffer[in], in);
        in = (in+1)%BufferSize; // Circular increment of 'in' index

        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&full); // Increment full count
    }
}

// Consumer thread function
void *consumer(void *cno)
{   
    for(int i = 0; i < MaxItems; i++) {
        sem_wait(&full); // Decrement full count; wait if buffer is empty
        pthread_mutex_lock(&mutex); // Lock the buffer

        int item = buffer[out]; // Remove item from buffer
        printf("Consumer %d: Remove Item %d from %d\n", *((int *)cno), item, out);
        out = (out+1)%BufferSize; // Circular increment of 'out' index

        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&empty); // Increment empty count
    }
}

int main()
{   
    pthread_t pro[3], con[3]; // Thread IDs for producers and consumers

    pthread_mutex_init(&mutex, NULL); // Initialize mutex
    sem_init(&empty, 0, BufferSize);  // Initialize empty semaphore with buffer size
    sem_init(&full, 0, 0);            // Initialize full semaphore with 0

    int a[3] = {1,2,3}; // Just used for numbering the producer and consumer

    // Create producer threads
    for(int i = 0; i < 3; i++) {
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
    }

    // Create consumer threads
    for(int i = 0; i < 3; i++) {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
    }

    // Wait for all producer threads to finish
    for(int i = 0; i < 3; i++) {
        pthread_join(pro[i], NULL);
    }

    // Wait for all consumer threads to finish
    for(int i = 0; i < 3; i++) {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex); // Destroy mutex
    sem_destroy(&empty);           // Destroy semaphores
    sem_destroy(&full);

    return 0;
}
