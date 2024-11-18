// FCFS
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> at(n), bt(n), ct(n), tat(n), wt(n);

    cout << "Enter Arrival Time and Burst Time for each process:\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << ": ";
        cin >> at[i] >> bt[i];
    }

    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        if (currentTime < at[i]) currentTime = at[i];
        ct[i] = currentTime + bt[i];
        currentTime = ct[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

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
1 5
2 1

*/