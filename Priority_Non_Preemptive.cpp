// priority non pre-emptive
#include <bits/stdc++.h>
using namespace std;

struct Process {
    int pid;      // Process ID
    int bt;       // CPU Burst time required
    int priority; // Priority of this process
};

// Function to sort the Process according to priority
bool comparison(Process a, Process b) {
    return (a.priority > b.priority); // Higher priority value means higher priority
}

// Function to find the waiting time for all processes
void findWaitingTime(Process proc[], int n, int wt[]) {
    wt[0] = 0; // Waiting time for first process is 0

    // Calculating waiting time for each process
    for (int i = 1; i < n; i++) {
        wt[i] = proc[i - 1].bt + wt[i - 1];
    }
}

// Function to calculate turnaround time
void findTurnAroundTime(Process proc[], int n, int wt[], int tat[]) {
    // Calculating turnaround time by adding burst time and waiting time
    for (int i = 0; i < n; i++) {
        tat[i] = proc[i].bt + wt[i];
    }
}

// Function to calculate average waiting time and turnaround time
void findavgTime(Process proc[], int n) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    // Find waiting time for all processes
    findWaitingTime(proc, n, wt);

    // Find turnaround time for all processes
    findTurnAroundTime(proc, n, wt, tat);

    // Display processes along with all details
    cout << "\nProcesses "
         << " Burst time "
         << " Waiting time "
         << " Turnaround time\n";

    // Calculate total waiting time and total turnaround time
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        cout << " " << proc[i].pid << "\t\t" << proc[i].bt
             << "\t " << wt[i] << "\t\t " << tat[i] << endl;
    }

    cout << "\nAverage waiting time = " << (float)total_wt / n;
    cout << "\nAverage turnaround time = " << (float)total_tat / n << endl;
}

// Function to perform Priority Scheduling
void priorityScheduling(Process proc[], int n) {
    // Sort processes by priority
    sort(proc, proc + n, comparison);

    cout << "\nOrder in which processes get executed: ";
    for (int i = 0; i < n; i++) {
        cout << proc[i].pid << " ";
    }
    cout << endl;

    findavgTime(proc, n);
}

// Main function
int main() {
    int n;

    // Take user input for the number of processes
    cout << "Enter the number of processes: ";
    cin >> n;

    // Create an array of processes
    Process proc[n];

    // Take user input for each process's burst time and priority
    for (int i = 0; i < n; i++) {
        cout << "\nEnter burst time and priority for process " << i + 1 << ":\n";
        proc[i].pid = i + 1;
        cout << "Burst time: ";
        cin >> proc[i].bt;
        cout << "Priority (higher number means higher priority): ";
        cin >> proc[i].priority;
    }

    // Perform Priority Scheduling
    priorityScheduling(proc, n);

    return 0;
}

/*Enter the number of processes: 2

Enter burst time and priority for process 1:
Burst time: 3
Priority (higher number means higher priority): 2

Enter burst time and priority for process 2:
Burst time: 1
Priority (higher number means higher priority): 1

Order in which processes get executed: 1 2 

Processes  Burst time  Waiting time  Turnaround time
 1		3	 0		 3
 2		1	 3		 4

Average waiting time = 1.5
Average turnaround time = 3.5
*/