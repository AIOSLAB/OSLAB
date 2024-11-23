// Online C++ compiler to run C++ program online
#include <bits/stdc++.h>
using namespace std;

typedef struct {
    string Pid;
    int at;         // Arrival time
    int bt;         // Burst time
    int ct = -1;    // Completion time
    int tat = -1;   // Turnaround time
    int wt = -1;    // Waiting time
    int priority;   // Priority
} Process;

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> pro(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter Process ID, Arrival time, Burst time, and Priority respectively: ";
        cin >> pro[i].Pid >> pro[i].at >> pro[i].bt >> pro[i].priority;
        cout << endl;
    }

    // Sort processes by arrival time
    sort(pro.begin(), pro.end(), [](const auto &a, const auto &b) {
        return a.at < b.at;
    });

    int currentTime = pro[0].at;
    currentTime += pro[0].bt;
    pro[0].ct = currentTime;

    // Mark the first process as completed by setting its priority to -1
    pro[0].priority = -1;

    int remainingProcesses = n - 1; // Number of processes left to complete

    while (remainingProcesses > 0) {
        int currentProcessIndex = -1;
        int maxPriority = -1; // Initialize to a low value for maximum priority selection

        // Find the process with the highest priority that has arrived and is not yet completed
        for (int i = 0; i < n; i++) {
            if (pro[i].at <= currentTime && pro[i].priority != -1 && pro[i].ct == -1) {
                if (pro[i].priority > maxPriority) { // Higher priority number means higher priority
                    currentProcessIndex = i;
                    maxPriority = pro[i].priority;
                }
            }
        }

        if (currentProcessIndex != -1) {
            currentTime += pro[currentProcessIndex].bt;
            pro[currentProcessIndex].ct = currentTime;
            pro[currentProcessIndex].priority = -1; // Mark as completed
            remainingProcesses--;
        } else {
            currentTime++; // Increment time if no process is ready
        }
    }

    // Calculate Turnaround Time (TAT) and Waiting Time (WT)
    for (int i = 0; i < n; i++) {
        pro[i].tat = pro[i].ct - pro[i].at;
        pro[i].wt = pro[i].tat - pro[i].bt;
    }

    // Display process times
    cout << "\nProcess ID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << pro[i].Pid << "\t\t" << pro[i].at << "\t\t" << pro[i].bt << "\t\t" << pro[i].priority
             << "\t\t" << pro[i].ct << "\t\t" << pro[i].tat << "\t\t" << pro[i].wt << endl;
    }

    // Calculate averages for Waiting Time and Turnaround Time
    double totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n; i++) {
        totalWT += pro[i].wt;
        totalTAT += pro[i].tat;
    }

    cout << "\nAverage Turnaround Time: " << totalTAT / n << endl;
    cout << "Average Waiting Time: " << totalWT / n << endl;

    return 0;
}

/*
Enter the number of processes: 4
Enter Process ID, Arrival time, Burst time, and Priority respectively: 1 0 5 10

Enter Process ID, Arrival time, Burst time, and Priority respectively: 2 1 4 20

Enter Process ID, Arrival time, Burst time, and Priority respectively: 3 2 2 30

Enter Process ID, Arrival time, Burst time, and Priority respectively: 4 4 1 40
*/
