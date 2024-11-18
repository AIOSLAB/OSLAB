#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int id, at, bt, ct, tat, wt;
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    cout << "Enter Arrival Time and Burst Time for each process:\n";
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cin >> processes[i].at >> processes[i].bt;
    }

    sort(processes.begin(), processes.end(),
         [](Process a, Process b) { return a.at < b.at; });

    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        auto it = min_element(processes.begin() + i, processes.end(),
                              [&](Process a, Process b) {
                                  return a.bt < b.bt && a.at <= currentTime;
                              });
        if (currentTime < it->at) currentTime = it->at;
        swap(processes[i], *it);
        processes[i].ct = currentTime + processes[i].bt;
        currentTime = processes[i].ct;
        processes[i].tat = processes[i].ct - processes[i].at;
        processes[i].wt = processes[i].tat - processes[i].bt;
    }

    cout << "\nP\tAT\tBT\tCT\tTAT\tWT\n";
    for (auto p : processes) {
        cout << "P" << p.id << "\t" << p.at << "\t" << p.bt << "\t" << p.ct
             << "\t" << p.tat << "\t" << p.wt << "\n";
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