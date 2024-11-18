// roundrobin
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int n, timeQuantum;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> at(n), bt(n), remaining_bt(n), ct(n), tat(n), wt(n);
    cout << "Enter Arrival Time and Burst Time for each process:\n";
    for (int i = 0; i < n; i++) {
        cin >> at[i] >> bt[i];
        remaining_bt[i] = bt[i];
    }

    cout << "Enter Time Quantum: ";
    cin >> timeQuantum;

    int currentTime = 0, completed = 0;
    queue<int> readyQueue;
    vector<bool> inQueue(n, false);

    // Add processes that arrive at time 0
    for (int i = 0; i < n; i++) {
        if (at[i] == 0) {
            readyQueue.push(i);
            inQueue[i] = true;
        }
    }

    while (completed < n) {
        // If the ready queue is empty, jump to the next process arrival time
        if (readyQueue.empty()) {
            for (int i = 0; i < n; i++) {
                if (remaining_bt[i] > 0) {
                    currentTime = at[i];
                    readyQueue.push(i);
                    inQueue[i] = true;
                    break;
                }
            }
        }

        int index = readyQueue.front();
        readyQueue.pop();
        inQueue[index] = false;

        // Execute the process for the time quantum or the remaining burst time
        int executionTime = min(timeQuantum, remaining_bt[index]);
        currentTime += executionTime;
        remaining_bt[index] -= executionTime;

        // Check for new arrivals during execution
        for (int i = 0; i < n; i++) {
            if (i != index && remaining_bt[i] > 0 && at[i] <= currentTime && !inQueue[i]) {
                readyQueue.push(i);
                inQueue[i] = true;
            }
        }

        // If the process is not yet completed, push it back into the queue
        if (remaining_bt[index] > 0) {
            readyQueue.push(index);
            inQueue[index] = true;
        } else {
            completed++;
            ct[index] = currentTime;
            tat[index] = ct[index] - at[index];
            wt[index] = tat[index] - bt[index];
        }
    }

    // Display the results
    cout << "\nP\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << "\t" << at[i] << "\t" << bt[i] << "\t" << ct[i]
             << "\t" << tat[i] << "\t" << wt[i] << "\n";
    }

    return 0;
}

/*
 Enter the no. of processes : 2
Enter arrival time and burst time for each process :
1 3
1 5
Enter time quantum : 2
*/