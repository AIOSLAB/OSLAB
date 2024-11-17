#include <bits/stdc++.h> // Includes all standard libraries in C++. Generally used in competitive programming.
#include <pthread.h> // Header file for POSIX threads (used for multithreading).
using namespace std; // Allows usage of standard library names without the `std::` prefix.

#define MAX 3 // Define the maximum dimension of the matrices as 3 (3x3 matrices).
#define MAX_THREAD 4 // Define the number of threads as 4.

int matA[MAX][MAX]; // Declare a 3x3 matrix for Matrix A.
int matB[MAX][MAX]; // Declare a 3x3 matrix for Matrix B.
int matC[MAX][MAX]; // Declare a 3x3 matrix for the result Matrix C.
int step_i = 0; // A shared variable to keep track of the current row being processed by threads.

// Function to perform matrix multiplication for a specific row, executed by threads.
void* mul(void* arg) {
    int i = step_i++; // Increment the shared variable to assign a row to the current thread.
    for (int j = 0; j < MAX; j++) { // Iterate over the columns of Matrix B.
        for (int k = 0; k < MAX; k++) { // Iterate over the columns of Matrix A (or rows of Matrix B).
            matC[i][j] += matA[i][k] * matB[k][j]; // Calculate the dot product for row `i` of A and column `j` of B.
        }
    }
    return nullptr; // Return null since the function's return type is void*.
}

int main() {
    cout << "Enter the values for Matrix A: " << endl;
    for (int i = 0; i < MAX; i++) { // Input elements for Matrix A row by row.
        for (int j = 0; j < MAX; j++) {
            cin >> matA[i][j]; // Store input into matA.
        }
    }

    cout << "Enter the values for Matrix B: " << endl;
    for (int i = 0; i < MAX; i++) { // Input elements for Matrix B row by row.
        for (int j = 0; j < MAX; j++) {
            cin >> matB[i][j]; // Store input into matB.
        }
    }

    // Declare threads to perform parallel processing.
    pthread_t threads[MAX_THREAD];

    // Create `MAX_THREAD` threads to compute parts of the matrix multiplication.
    for (int i = 0; i < MAX_THREAD; i++) {
        pthread_create(&threads[i], NULL, mul, nullptr); // Create a thread to execute the `mul` function.
    }

    // Wait for all threads to complete execution.
    for (int i = 0; i < MAX_THREAD; i++) {
        pthread_join(threads[i], NULL); // Block the main thread until thread `i` completes.
    }

    // Display the result matrix (Matrix C) after computation.
    cout << "Final values for Matrix C: " << endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cout << matC[i][j] << " "; // Print each element in Matrix C.
        }
        cout << endl; // Move to the next row.
    }

    return 0; // Exit the program.
}


// Commands to run:
// sudo apt install g++
// g++ Matrix_multiplication.cpp
// ./a.out