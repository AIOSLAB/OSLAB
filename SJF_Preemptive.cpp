#include <bits/stdc++.h>
using namespace std;

struct process {
    int id;     // Process ID
    int at;     // Arrival time
    int bt;     // Burst time
    int ct;     // Completion time
    int tat;    // Turnaround time
    int wt;     // Waiting time
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    process pro[n];
    vector<int> originalBurstTime(n);

    // Taking input for processes
    for (int i = 0; i < n; i++) {
        pro[i].id = i + 1; // Assign process IDs automatically
        cout << "Enter details for process " << pro[i].id << ":" << endl;
        cout << "Arrival time: ";
        cin >> pro[i].at;
        cout << "Burst time: ";
        cin >> pro[i].bt;

        originalBurstTime[i] = pro[i].bt; // Storing original burst time
    }

    int currTime = 0;
    int completed = 0; // Number of processes completed
    vector<int> completionTime(n, -1);

    while (completed < n) {
        int shortest = -1;
        int minBurst = INT_MAX;

        // Find the process with the shortest remaining burst time
        for (int i = 0; i < n; i++) {
            if (pro[i].at <= currTime && pro[i].bt < minBurst && pro[i].bt > 0) {
                minBurst = pro[i].bt;
                shortest = i;
            }
        }

        if (shortest == -1) {
            currTime++;
            continue;
        }

        pro[shortest].bt -= 1;
        currTime++;

        if (pro[shortest].bt == 0) {
            completionTime[shortest] = currTime;
            completed++;
        }
    }

    cout << endl;

    // Calculating Turnaround Time
    vector<int> tat(n);
    for (int i = 0; i < n; i++) {
        tat[i] = completionTime[i] - pro[i].at;
    }

    // Calculating Waiting Time
    vector<int> waitingTime(n);
    for (int i = 0; i < n; i++) {
        waitingTime[i] = tat[i] - originalBurstTime[i];
    }

    cout << endl;

    // Display process times
    cout << "Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time" << endl;
    for (int i = 0; i < n; i++) {
        cout << "P" << pro[i].id << "\t\t" << pro[i].at << "\t\t" << originalBurstTime[i]
             << "\t\t" << completionTime[i] << "\t\t" << tat[i] << "\t\t" << waitingTime[i] << endl;
    }

    // Print averages for waiting time and completion time
    float ct_avg = accumulate(completionTime.begin(), completionTime.end(), 0.0) / n;
    float wt_avg = accumulate(waitingTime.begin(), waitingTime.end(), 0.0) / n;

    cout << endl;
    cout << "Average Completion Time: " << ct_avg << endl;
    cout << "Average Waiting Time: " << wt_avg << endl;

    return 0;
}
/*
Enter the number of processes: 4
Enter details for process 1:
Arrival time: 0
Burst time: 5
Enter details for process 2:
Arrival time: 1
Burst time: 3
Enter details for process 3:
Arrival time: 2
Burst time: 4
Enter details for process 4:
Arrival time: 4
Burst time: 1
*/
