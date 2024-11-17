// Bankers algo
#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

// Function to check if the system is in a safe state
bool isSafeState(int processes[], int avail[], int max[][MAX_RESOURCES], int alloc[][MAX_RESOURCES], int need[][MAX_RESOURCES], int num_processes, int num_resources) {
    bool finish[MAX_PROCESSES] = {false};
    int safeSequence[MAX_PROCESSES];
    int work[MAX_RESOURCES];
    
    // Initialize work as available resources
    for (int i = 0; i < num_resources; i++) {
        work[i] = avail[i];
    }

    int count = 0;
    
    // Find the processes that can finish
    while (count < num_processes) {
        bool found = false;
        for (int p = 0; p < num_processes; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < num_resources; j++) {
                    if (need[p][j] > work[j])
                        break;
                }
                
                // If all resources for process p can be allocated
                if (j == num_resources) {
                    // Process p can finish
                    for (int k = 0; k < num_resources; k++) {
                        work[k] += alloc[p][k];
                    }
                    safeSequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        // If no process could be found in this iteration, system is not in a safe state
        if (!found) {
            return false;
        }
    }
    
    // If all processes can finish, system is in a safe state
    printf("System is in a safe state.\nSafe Sequence: ");
    for (int i = 0; i < num_processes; i++) {
        printf("%d ", safeSequence[i]);
    }
    printf("\n");
    return true;
}

// Function to calculate the need matrix
void calculateNeed(int need[][MAX_RESOURCES], int max[][MAX_RESOURCES], int alloc[][MAX_RESOURCES], int num_processes, int num_resources) {
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

int main() {
    int num_processes, num_resources;
    
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);

    int processes[MAX_PROCESSES], avail[MAX_RESOURCES], max[MAX_PROCESSES][MAX_RESOURCES], alloc[MAX_PROCESSES][MAX_RESOURCES], need[MAX_PROCESSES][MAX_RESOURCES];

    // Input the available resources
    printf("Enter the available resources: \n");
    for (int i = 0; i < num_resources; i++) {
        scanf("%d", &avail[i]);
    }

    // Input the maximum demand of each process
    printf("Enter the maximum demand of each process: \n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input the allocated resources for each process
    printf("Enter the allocated resources for each process: \n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Calculate the need matrix
    calculateNeed(need, max, alloc, num_processes, num_resources);

    // Check if the system is in a safe state
    if (!isSafeState(processes, avail, max, alloc, need, num_processes, num_resources)) {
        printf("System is not in a safe state.\n");
    }

    return 0;
}


// Sample Input:
/*
Enter the number of processes: 5
Enter the number of resources: 3
Enter the available resources: 
3 3 2
Enter the maximum demand of each process: 
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3 
Enter the allocated resources for each process: 
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
*/