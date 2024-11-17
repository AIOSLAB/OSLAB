import java.util.Scanner;

public class BankersAlgorithm {
    // Variables for number of processes and resources
    private int numProcesses;
    private int numResources;

    // Matrices and arrays for the Banker's algorithm
    private int[][] allocation; // Allocation matrix: resources currently allocated to each process
    private int[][] max;        // Max matrix: maximum demand of each process
    private int[][] need;       // Need matrix: additional resources each process needs to complete
    private int[] available;    // Available array: resources currently available in the system

    // Constructor to initialize matrices and arrays
    public BankersAlgorithm(int processes, int resources) {
        numProcesses = processes; // Number of processes
        numResources = resources; // Number of resources
        allocation = new int[processes][resources]; // Allocation matrix initialization
        max = new int[processes][resources];        // Max matrix initialization
        need = new int[processes][resources];       // Need matrix initialization
        available = new int[resources];            // Available array initialization
    }

    // Method to input allocation, max, and available matrices from the user
    public void inputMatrices() {
        Scanner scanner = new Scanner(System.in);

        // Input Allocation matrix
        System.out.println("Enter Allocation matrix: ");
        for (int i = 0; i < numProcesses; i++) {
            for (int j = 0; j < numResources; j++) {
                allocation[i][j] = scanner.nextInt();
            }
        }

        // Input Max matrix
        System.out.println("Enter Max matrix: ");
        for (int i = 0; i < numProcesses; i++) {
            for (int j = 0; j < numResources; j++) {
                max[i][j] = scanner.nextInt();
            }
        }

        // Input Available resources array
        System.out.println("Enter Available resources: ");
        for (int i = 0; i < numResources; i++) {
            available[i] = scanner.nextInt();
        }

        // Calculate the Need matrix: `Need = Max - Allocation`
        for (int i = 0; i < numProcesses; i++) {
            for (int j = 0; j < numResources; j++) {
                need[i][j] = max[i][j] - allocation[i][j];
            }
        }

        scanner.close();
    }

    // Method to check if the system is in a safe state
    public boolean checkSafeState() {
        boolean[] finished = new boolean[numProcesses]; // Tracks if a process is finished
        int[] work = new int[numResources]; // Work array to simulate available resources
        System.arraycopy(available, 0, work, 0, numResources); // Copy available to work array

        StringBuilder safeSequence = new StringBuilder(); // To store the safe sequence
        int count = 0; // Number of finished processes

        // Loop until all processes are checked or no further allocation is possible
        while (count < numProcesses) {
            boolean found = false;

            // Check each process to see if its need can be satisfied
            for (int i = 0; i < numProcesses; i++) {
                if (!finished[i]) { // Process is not yet finished
                    boolean canAllocate = true;

                    // Check if the current process's need can be met
                    for (int j = 0; j < numResources; j++) {
                        if (need[i][j] > work[j]) {
                            canAllocate = false; // Need exceeds available resources
                            break;
                        }
                    }

                    if (canAllocate) {
                        // Allocate resources to process i and mark it as finished
                        for (int j = 0; j < numResources; j++) {
                            work[j] += allocation[i][j]; // Release resources after completion
                        }
                        safeSequence.append(i).append(" "); // Add process to safe sequence
                        finished[i] = true;
                        found = true;
                        count++;
                    }
                }
            }

            if (!found) {
                // If no process could be allocated resources, the system is unsafe
                System.out.println("System is not in a safe state.");
                return false;
            }
        }

        // If all processes are finished, the system is in a safe state
        System.out.println("System is in a safe state. Safe sequence is: " + safeSequence);
        return true;
    }

    // Main method to execute the Banker's Algorithm
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Input number of processes and resources
        System.out.println("Enter the number of processes: ");
        int processes = scanner.nextInt();

        System.out.println("Enter the number of resources: ");
        int resources = scanner.nextInt();

        // Create a Banker's Algorithm object and input matrices
        BankersAlgorithm bankers = new BankersAlgorithm(processes, resources);
        bankers.inputMatrices();

        // Check and display if the system is in a safe state
        bankers.checkSafeState();

        scanner.close();
    }
}


// Commands to run:
// javac BankersAlgorithm.java
// java BankersAlgorithm

// Sample input:
/*
Enter the number of processes: 
5
Enter the number of resources: 
3
Enter Allocation matrix: 
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
Enter Max matrix: 
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
Enter Available resources: 
3 3 2
*/