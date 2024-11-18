// priority pre-emptive 
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int pid;       // Process ID
    int at;        // Arrival Time
    int bt;        // Burst Time
    int priority;  // Priority (higher value means higher priority)
    int remaining_bt; // Remaining Burst Time
    int ct;        // Completion Time
    int tat;       // Turnaround Time
    int wt;        // Waiting Time
};

void findAvgTime(vector<Process> &processes, int n) {
    int currentTime = 0;
    int completed = 0;
    int maxPriorityIndex;
    bool found;
    float totalWT = 0, totalTAT = 0;

    while (completed != n) {
        maxPriorityIndex = -1;
        found = false;

        // Find the process with the highest priority (highest priority value)
        for (int i = 0; i < n; i++) {
            if (processes[i].at <= currentTime && processes[i].remaining_bt > 0) {
                if (maxPriorityIndex == -1 || processes[i].priority > processes[maxPriorityIndex].priority) {
                    maxPriorityIndex = i;
                    found = true;
                }
            }
        }

        // If no process is found, increment the current time
        if (!found) {
            currentTime++;
            continue;
        }

        // Execute the selected process for one unit of time
        processes[maxPriorityIndex].remaining_bt--;
        currentTime++;

        // If the process is completed
        if (processes[maxPriorityIndex].remaining_bt == 0) {
            completed++;
            processes[maxPriorityIndex].ct = currentTime;
            processes[maxPriorityIndex].tat = processes[maxPriorityIndex].ct - processes[maxPriorityIndex].at;
            processes[maxPriorityIndex].wt = processes[maxPriorityIndex].tat - processes[maxPriorityIndex].bt;
            totalWT += processes[maxPriorityIndex].wt;
            totalTAT += processes[maxPriorityIndex].tat;
        }
    }

    // Print process details
    cout << "\nP\tAT\tBT\tPriority\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i].pid << "\t" << processes[i].at << "\t" << processes[i].bt << "\t"
             << processes[i].priority << "\t\t" << processes[i].ct << "\t" << processes[i].tat << "\t"
             << processes[i].wt << "\n";
    }

    cout << "\nAverage Waiting Time: " << (totalWT / n);
    cout << "\nAverage Turnaround Time: " << (totalTAT / n) << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Enter Arrival Time, Burst Time, and Priority for Process " << processes[i].pid << ": ";
        cin >> processes[i].at >> processes[i].bt >> processes[i].priority;
        processes[i].remaining_bt = processes[i].bt;
    }

    // Find average time and display process details
    findAvgTime(processes, n);

    return 0;
}

/* Enter the number of processes: 3
Enter Arrival Time, Burst Time, and Priority for Process 1: 1 3 1
Enter Arrival Time, Burst Time, and Priority for Process 2: 2 3 2
Enter Arrival Time, Burst Time, and Priority for Process 3: 3 1 0

P	AT	BT	Priority	CT	TAT	WT
P1	1	3	1		7	6	3
P2	2	3	2		5	3	0
P3	3	1	0		8	5	4

Average Waiting Time: 2.33333
Average Turnaround Time: 4.66667
*/