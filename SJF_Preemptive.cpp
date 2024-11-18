// SJF Preemptive
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> at(n), bt(n), remaining_bt(n), ct(n), tat(n), wt(n);
    cout << "Enter Arrival Time and Burst Time for each process:\n";
    for (int i = 0; i < n; i++) {
        cin >> at[i] >> bt[i];
        remaining_bt[i] = bt[i];
    }

    int completed = 0, currentTime = 0, minIndex = -1, minTime = INT_MAX;

    while (completed != n) {
        minIndex = -1;
        minTime = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (at[i] <= currentTime && remaining_bt[i] > 0 && remaining_bt[i] < minTime) {
                minTime = remaining_bt[i];
                minIndex = i;
            }
        }

        if (minIndex == -1) {
            currentTime++;
            continue;
        }

        remaining_bt[minIndex]--;
        currentTime++;

        if (remaining_bt[minIndex] == 0) {
            completed++;
            ct[minIndex] = currentTime;
            tat[minIndex] = ct[minIndex] - at[minIndex];
            wt[minIndex] = tat[minIndex] - bt[minIndex];
        }
    }

    cout << "\nP\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << "\t" << at[i] << "\t" << bt[i] << "\t" << ct[i]
             << "\t" << tat[i] << "\t" << wt[i] << "\n";
    }

    return 0;
}


/*
 Enter the no. of processes : 3
Enter arrival time and burst time for each process :
1 3
1 5
2 1
*/