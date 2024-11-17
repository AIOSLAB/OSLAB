#include <stdio.h>  // Standard input/output library
#include <stdlib.h> // For abs() and other utilities
#include <stdbool.h> // For boolean data type

#define MAX 100 // Maximum size for request arrays

// Function to calculate the absolute difference
int abs_diff(int a, int b) {
    return abs(a - b); // Return the absolute difference between two integers
}

// SSTF Algorithm
void sstf(int requests[], int n, int head) {
    bool processed[MAX] = {false}; // Track whether a request has been processed
    int current_head = head; // Start from the initial head position

    printf("\nSSTF Disk Scheduling:\n");
    printf("Order of requests: ");

    for (int i = 0; i < n; i++) { // Loop through all requests
        int min_distance = MAX; // Initialize minimum distance to a high value
        int next_index = -1; // Index of the next closest request

        for (int j = 0; j < n; j++) { // Iterate over all requests
            if (!processed[j]) { // If the request is not yet processed
                int distance = abs_diff(current_head, requests[j]); // Calculate distance
                if (distance < min_distance) { // Update if closer request is found
                    min_distance = distance;
                    next_index = j;
                }
            }
        }

        processed[next_index] = true; // Mark the request as processed
        current_head = requests[next_index]; // Move head to the request position
        printf("%d ", current_head); // Print the request being processed
    }
    printf("\n");
}

// SCAN Algorithm
void scan(int requests[], int n, int head, int disk_size) {
    int requests_sorted[MAX + 1]; // Include the head position for sorting
    requests_sorted[0] = head; // Add the initial head position to the list

    for (int i = 0; i < n; i++) {
        requests_sorted[i + 1] = requests[i]; // Copy all requests into the array
    }

    n++; // Include the head position in the count

    // Sort the requests array (including the head position) in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (requests_sorted[i] > requests_sorted[j]) { // Swap if out of order
                int temp = requests_sorted[i];
                requests_sorted[i] = requests_sorted[j];
                requests_sorted[j] = temp;
            }
        }
    }

    int pos; // Position of the initial head in the sorted array
    for (int i = 0; i < n; i++) {
        if (requests_sorted[i] == head) { // Find the head position
            pos = i;
            break;
        }
    }

    printf("\nSCAN Disk Scheduling:\n");
    printf("Order of requests: ");

    for (int i = pos; i < n; i++) { // Process requests moving towards the end
        printf("%d ", requests_sorted[i]);
    }

    printf("%d ", disk_size - 1); // Move to the end of the disk (maximum track)

    for (int i = pos - 1; i >= 0; i--) { // Process requests moving back
        printf("%d ", requests_sorted[i]);
    }
    printf("\n");
}

// C-LOOK Algorithm
void clook(int requests[], int n, int head) {
    int requests_sorted[MAX]; // Array to hold sorted requests

    for (int i = 0; i < n; i++) {
        requests_sorted[i] = requests[i]; // Copy requests to another array
    }

    // Sort the requests in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (requests_sorted[i] > requests_sorted[j]) { // Swap if out of order
                int temp = requests_sorted[i];
                requests_sorted[i] = requests_sorted[j];
                requests_sorted[j] = temp;
            }
        }
    }

    int pos; // Position of the first request >= head
    for (int i = 0; i < n; i++) {
        if (requests_sorted[i] >= head) { // Find the first request not smaller than the head
            pos = i;
            break;
        }
    }

    printf("\nC-LOOK Disk Scheduling:\n");
    printf("Order of requests: ");

    for (int i = pos; i < n; i++) { // Process from current head to the end
        printf("%d ", requests_sorted[i]);
    }

    for (int i = 0; i < pos; i++) { // Process from the start of the disk to the position
        printf("%d ", requests_sorted[i]);
    }
    printf("\n");
}

int main() {
    int n, head, disk_size; // Variables for number of requests, head position, and disk size
    int requests[MAX]; // Array to store disk requests

    printf("Enter the number of disk requests: ");
    scanf("%d", &n); // Input the number of requests

    printf("Enter the disk size: ");
    scanf("%d", &disk_size); // Input the size of the disk (maximum track number)

    printf("Enter the initial head position: ");
    scanf("%d", &head); // Input the initial head position

    printf("Enter the disk requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]); // Input all disk requests
    }

    // Call SSTF Algorithm
    sstf(requests, n, head);

    // Call SCAN Algorithm
    scan(requests, n, head, disk_size);

    // Call C-LOOK Algorithm
    clook(requests, n, head);

    return 0; // Exit the program
}


// Sample Input:
/*
Enter the number of disk requests: 8
Enter the disk size: 200
Enter the initial head position: 50
Enter the disk requests:
98 183 41 122 14 124 65 67
*/