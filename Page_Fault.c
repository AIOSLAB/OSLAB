#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGES 100 // Maximum number of pages allowed in the reference string
#define MAX_FRAMES 10 // Maximum number of frames available

// Function prototypes for page replacement algorithms
int fifo(int pages[], int n, int frames);    // FIFO page replacement algorithm
int lru(int pages[], int n, int frames);     // LRU page replacement algorithm
int optimal(int pages[], int n, int frames); // Optimal page replacement algorithm

int main() {    
    int pages[MAX_PAGES]; // Array to store the reference string (pages)
    int n, frames;        // Number of pages and number of available frames

    // Input the number of pages
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    // Input the reference string (sequence of page requests)
    printf("Enter the reference string (space-separated): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Input the number of frames available for page replacement
    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    // Calculate and store the number of page faults for each algorithm
    int fifo_faults = fifo(pages, n, frames);
    int lru_faults = lru(pages, n, frames);
    int optimal_faults = optimal(pages, n, frames);

    // Display the page fault counts for all three algorithms
    printf("\nPage Faults:\n");
    printf("FIFO: %d\n", fifo_faults);
    printf("LRU: %d\n", lru_faults);
    printf("Optimal: %d\n", optimal_faults);

    return 0; // Exit the program
}

// FIFO Page Replacement Algorithm
int fifo(int pages[], int n, int frames) {
    int page[frames];       // Array to store pages in memory (frames)
    int page_faults = 0;    // Counter for page faults
    int index = 0;          // Index to maintain the FIFO queue
    int found, i;

    // Initialize all frames to -1 (indicating empty)
    for (i = 0; i < frames; i++) {
        page[i] = -1;
    }

    // Traverse each page in the reference string
    for (i = 0; i < n; i++) {
        found = 0; // Flag to indicate if the page is already in frames

        // Check if the page is already in memory
        for (int j = 0; j < frames; j++) {
            if (page[j] == pages[i]) {
                found = 1; // Page is in memory, no fault
                break;
            }
        }

        // If page is not found, replace the oldest page
        if (!found) {
            page[index] = pages[i];                 // Replace page at the current index
            index = (index + 1) % frames;          // Move the index in a circular manner
            page_faults++;                         // Increment page fault count
        }
    }
    return page_faults; // Return total page faults
}

// LRU Page Replacement Algorithm
int lru(int pages[], int n, int frames) {
    int page[frames];        // Array to store pages in memory
    int page_faults = 0;     // Counter for page faults
    int found, i, j, lru_index;    
    int lru_time[MAX_FRAMES] = {0}; // Array to store the last used time of pages

    // Initialize all frames to -1 (empty) and reset usage times
    for (i = 0; i < frames; i++) {
        page[i] = -1;
    }

    // Traverse each page in the reference string
    for (i = 0; i < n; i++) {
        found = 0; // Flag to indicate if the page is already in frames

        // Check if the page is already in memory
        for (j = 0; j < frames; j++) {
            if (page[j] == pages[i]) {
                found = 1;           // Page is in memory
                lru_time[j] = i;     // Update its last used time
                break;
            }
        }

        // If page is not found, replace the least recently used page
        if (!found) {
            lru_index = 0; // Find the least recently used page
            for (j = 1; j < frames; j++) {
                if (lru_time[j] < lru_time[lru_index]) {
                    lru_index = j;
                }
            }
            page[lru_index] = pages[i]; // Replace the LRU page
            lru_time[lru_index] = i;    // Update its usage time
            page_faults++;              // Increment page fault count
        }
    }
    return page_faults; // Return total page faults
}

// Optimal Page Replacement Algorithm
int optimal(int pages[], int n, int frames) {
    int page[frames];     // Array to store pages in memory
    int page_faults = 0;  // Counter for page faults
    int found, i, j, k, farthest;

    // Initialize all frames to -1 (empty)
    for (i = 0; i < frames; i++) {
        page[i] = -1;
    }

    // Traverse each page in the reference string
    for (i = 0; i < n; i++) {
        found = 0; // Flag to indicate if the page is already in frames

        // Check if the page is already in memory
        for (j = 0; j < frames; j++) {
            if (page[j] == pages[i]) {
                found = 1; // Page is in memory, no fault
                break;
            }
        }

        // If page is not found, replace the page that is used farthest in the future
        if (!found) {
            farthest = -1;            // To track the farthest used page
            int index_to_replace = -1;

            // Check future usage of each page in memory
            for (j = 0; j < frames; j++) {
                for (k = i + 1; k < n; k++) {
                    if (page[j] == pages[k]) {
                        if (k > farthest) {
                            farthest = k;
                            index_to_replace = j;
                        }
                        break;
                    }
                }
                // If a page is not used again in the future, select it for replacement
                if (k == n) {
                    index_to_replace = j;
                    break;
                }
            }
            page[index_to_replace] = pages[i]; // Replace the optimal page
            page_faults++;                     // Increment page fault count
        }
    }
    return page_faults; // Return total page faults
}

// Sample Input:
/*
Enter the number of pages: 12
Enter the reference string (space-separated): 7 0 1 2 0 3 0 4 2 3 0 3
Enter the number of frames: 3
*/