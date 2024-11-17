#include <iostream>
#include <pthread.h>  // Header for POSIX threads (for multithreading).
#include <semaphore.h> // Header for semaphores.
#include <unistd.h>    // Header for sleep function.
using namespace std;

// Declare semaphores and mutex
sem_t wrt; // Semaphore to control access to the shared resource for writers.
pthread_mutex_t mutex; // Mutex to ensure mutual exclusion for updating `read_count`.

int read_count = 0; // Keeps track of the number of active readers.
int value = 0;      // The shared resource to be read and written by threads.

// Writer thread function
void *writer(void *arg) {
    while (true) {
        sem_wait(&wrt); // Wait (lock) the semaphore to get exclusive access to the shared resource.

        // Critical section: writer updates the shared resource.
        value++;
        cout << "Writer wrote value: " << value << endl;

        sem_post(&wrt); // Signal (unlock) the semaphore, allowing others to access the resource.
        sleep(1); // Pause for a moment to simulate real-time processing.
    }
    return NULL;
}

// Reader thread function
void *reader(void *arg) {
    while (true) {
        // Lock the mutex to safely update `read_count`.
        pthread_mutex_lock(&mutex); 
        read_count++; // Increment the count of active readers.

        // If this is the first reader, lock the writer semaphore to block writers.
        if (read_count == 1) {
            sem_wait(&wrt); 
        }
        pthread_mutex_unlock(&mutex); // Unlock the mutex after updating `read_count`.

        // Critical section: reader reads the shared resource.
        cout << "Reader read value: " << value << endl;

        // Lock the mutex to safely update `read_count` again.
        pthread_mutex_lock(&mutex);
        read_count--; // Decrement the count of active readers.

        // If there are no readers left, unlock the writer semaphore.
        if (read_count == 0) {
            sem_post(&wrt);
        }
        pthread_mutex_unlock(&mutex); // Unlock the mutex after updating `read_count`.
        sleep(1); // Pause for a moment to simulate real-time processing.
    }
    return NULL;
}

int main() {
    pthread_t readers[3], writers[3]; // Create arrays of threads for readers and writers.

    // Initialize the semaphore and mutex
    sem_init(&wrt, 0, 1); // Initialize writer semaphore to 1, allowing one writer or multiple readers.
    pthread_mutex_init(&mutex, NULL); // Initialize the mutex for reader count management.

    // Create writer threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&writers[i], NULL, writer, NULL);
    }

    // Create reader threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&readers[i], NULL, reader, NULL);
    }

    // Wait for all threads to complete execution (infinite loop means this won't end naturally).
    for (int i = 0; i < 3; i++) {
        pthread_join(writers[i], NULL);
        pthread_join(readers[i], NULL);
    }

    // Destroy the semaphore and mutex after all threads are done.
    sem_destroy(&wrt); // Clean up the writer semaphore.
    pthread_mutex_destroy(&mutex); // Clean up the mutex.

    return 0; // Exit the program.
}

// Commands to run:
// sudo apt install g++
// g++ Reader_Writer.cpp
// ./a.out