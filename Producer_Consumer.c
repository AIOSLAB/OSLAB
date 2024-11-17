#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Shared buffer for producer-consumer communication
int *buffer;  
int buffer_size, in = 0, out = 0; // Buffer size and indices for circular buffer
int item_count; // Number of items to produce/consume

// Semaphores and mutex for synchronization
sem_t empty; // Counts the number of empty slots in the buffer
sem_t full;  // Counts the number of filled slots in the buffer
pthread_mutex_t mutex; // Mutex to protect buffer access

// Function to produce an item (returns a random integer)
int produce_item() {
    return rand() % 100;  
}

// Function to consume an item (prints the consumed item)
void consume_item(int item) {
    printf("Consumed: %d\n", item);
}

// Producer thread function
void* producer(void* arg) {
    int id = *((int *)arg); // Producer ID
    int item;

    // Each producer produces `item_count` items
    for (int i = 0; i < item_count; i++) {
        item = produce_item(); // Generate a new item

        sem_wait(&empty); // Wait if the buffer is full
        pthread_mutex_lock(&mutex); // Lock the buffer for exclusive access

        // Add the item to the buffer and update the `in` index
        buffer[in] = item;
        printf("Producer %d produced: %d\n", id, item);
        in = (in + 1) % buffer_size; // Use modulo for circular buffer

        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&full); // Signal that a new item is available

        sleep(1); // Simulate production time
    }
    return NULL;
}

// Consumer thread function
void* consumer(void* arg) {
    int id = *((int *)arg); // Consumer ID
    int item;

    // Each consumer consumes `item_count` items
    for (int i = 0; i < item_count; i++) {
        sem_wait(&full); // Wait if the buffer is empty
        pthread_mutex_lock(&mutex); // Lock the buffer for exclusive access

        // Remove an item from the buffer and update the `out` index
        item = buffer[out];
        printf("Consumer %d consumed: %d\n", id, item);
        out = (out + 1) % buffer_size; // Use modulo for circular buffer

        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&empty); // Signal that a slot is now empty

        sleep(1); // Simulate consumption time
    }
    return NULL;
}

// Main function
int main() {
    int producers_count, consumers_count;

    // Get buffer size, number of producers, number of consumers, and item count from the user
    printf("Enter the buffer size: ");
    scanf("%d", &buffer_size);

    printf("Enter the number of producers: ");
    scanf("%d", &producers_count);

    printf("Enter the number of consumers: ");
    scanf("%d", &consumers_count);

    printf("Enter the number of items to produce/consume: ");
    scanf("%d", &item_count);

    // Allocate memory for the buffer
    buffer = (int *)malloc(buffer_size * sizeof(int));

    // Initialize semaphores and mutex
    sem_init(&empty, 0, buffer_size);  // Initially, all slots are empty
    sem_init(&full, 0, 0);             // Initially, no slots are full
    pthread_mutex_init(&mutex, NULL); // Initialize the mutex

    // Create producer and consumer threads
    pthread_t producers[producers_count], consumers[consumers_count];
    int producer_ids[producers_count], consumer_ids[consumers_count];

    // Create producer threads
    for (int i = 0; i < producers_count; i++) {
        producer_ids[i] = i + 1; // Assign a unique ID to each producer
        pthread_create(&producers[i], NULL, producer, (void *)&producer_ids[i]);
    }

    // Create consumer threads
    for (int i = 0; i < consumers_count; i++) {
        consumer_ids[i] = i + 1; // Assign a unique ID to each consumer
        pthread_create(&consumers[i], NULL, consumer, (void *)&consumer_ids[i]);
    }

    // Wait for all producer threads to complete
    for (int i = 0; i < producers_count; i++) {
        pthread_join(producers[i], NULL);
    }

    // Wait for all consumer threads to complete
    for (int i = 0; i < consumers_count; i++) {
        pthread_join(consumers[i], NULL);
    }

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    // Free allocated memory for the buffer
    free(buffer);

    return 0; // Exit the program
}


// Commands to run:
// sudo apt update
// sudo apt install gcc
// gcc Producer_Consumer.c -o Producer_Consumer
// ./Producer_Consumer