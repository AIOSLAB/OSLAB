#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

// Function prototypes for sorting algorithms
void bubbleSort(int arr[], int n); // Prototype for Bubble Sort
void insertionSort(int arr[], int n); // Prototype for Insertion Sort

int main() {
    int n; // Number of elements in the array
    printf("Enter the number of elements: ");
    scanf("%d", &n); // Input the number of elements

    int arr[n]; // Declare an array of size `n`
    printf("Enter %d integers:\n", n); // Prompt user for array elements
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]); // Input array elements
    }

    pid_t pid = fork(); // Create a child process

    if (pid < 0) { // Check if fork() failed
        perror("Fork failed"); // Print error if fork fails
        exit(1); // Exit program
    } else if (pid == 0) { // Code executed by child process
        printf("\nChild process (PID: %d) is sorting the array using insertion sort.\n", getpid());
        insertionSort(arr, n); // Sort the array using insertion sort
        printf("Child process sorted array: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]); // Print sorted array
        }
        printf("\nChild process exiting.\n");
        exit(0); // Child process exits
    } else { // Code executed by parent process
        sleep(2); // Parent process sleeps for 2 seconds (child becomes zombie)
        printf("\nParent process (PID: %d) is sorting the array using bubble sort.\n", getpid());
        bubbleSort(arr, n); // Sort the array using bubble sort
        printf("Parent process sorted array: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]); // Print sorted array
        }
        printf("\n");

        int status; 
        wait(&status); // Parent waits for child process to finish, removing zombie state

        printf("\nParent process detected child process termination.\n");

        if (fork() == 0) { // Create a second child process
            printf("\nOrphan child process (PID: %d), parent PID: %d\n", getpid(), getppid());
            sleep(5); // Simulate orphan process execution
            printf("Orphan child process (PID: %d) now adopted by init (PID: %d)\n", getpid(), getppid());
            exit(0); // Orphan process exits
        }

        printf("Parent process exiting.\n");
        exit(0); // Parent exits, orphaning the second child process
    }

    return 0;
}

// Bubble sort implementation
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) { // Outer loop for passes
        for (int j = 0; j < n-i-1; j++) { // Inner loop for comparisons
            if (arr[j] > arr[j+1]) { // Compare adjacent elements
                int temp = arr[j]; // Swap elements if needed
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Insertion sort implementation
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) { // Iterate through unsorted elements
        int key = arr[i]; // Current element to insert
        int j = i - 1;
        while (j >= 0 && arr[j] > key) { // Move elements greater than key
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key; // Insert the key
    }
}


// Commands to run:
// sudo apt update
// sudo apt install gcc
// gcc Zombie_Orphan.c -o Zombie_Orphan
// ./Zombie_Orphan