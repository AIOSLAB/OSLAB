#include <bits/stdc++.h>
using namespace std;

struct process {
    int id;
    int at;  // Arrival Time
    int bt;  // Burst Time
    int ct;  // Completion Time
    int tat; // Turnaround Time
    int wt;  // Waiting Time
};

void find_sjf_non_pre(process pro[], int n) {
    int remainingTime[n];
    for (int i = 0; i < n; i++) {
        remainingTime[i] = pro[i].bt;
    }

    int currentTime = 0;
    int complete = 0; // number of processes completed till now
    int shortest = 0; // index of minimum burst time
    int minBurst = INT_MAX; // store minimum burst time within current time

    while (complete < n) {
        minBurst = INT_MAX;
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (pro[i].at <= currentTime && remainingTime[i] < minBurst && remainingTime[i] > 0) {
                minBurst = remainingTime[i];
                shortest = i;
                found = true;
            }
        }

        if (!found) {
            currentTime++;
            continue;
        }

        remainingTime[shortest]--;
        currentTime++;

        if (remainingTime[shortest] == 0) {
            complete++;
            pro[shortest].ct = currentTime;
            pro[shortest].tat = pro[shortest].ct - pro[shortest].at;
            pro[shortest].wt = pro[shortest].tat - pro[shortest].bt;
        }
    }
}

void print_sjf_non_pre(process pro[], int n) {
    cout << "Id\t AT\t BT\t CT\t TAT\t WT\t" << endl;
    for (int i = 0; i < n; i++) {
        cout << pro[i].id << " \t " << pro[i].at << " \t " << pro[i].bt << " \t " << pro[i].ct << " \t " << pro[i].tat << " \t " << pro[i].wt << endl;
    }
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    process pro[n];

    // Take input for each process
    for (int i = 0; i < n; i++) {
        cout << "Enter details for Process " << i + 1 << ":\n";
        pro[i].id = i + 1; // Assign process ID
        cout << "Arrival Time: ";
        cin >> pro[i].at;
        cout << "Burst Time: ";
        cin >> pro[i].bt;
        pro[i].ct = 0;  // Initialize Completion Time
        pro[i].tat = 0; // Initialize Turnaround Time
        pro[i].wt = 0;  // Initialize Waiting Time
    }

    find_sjf_non_pre(pro, n);
    print_sjf_non_pre(pro, n);

    return 0;
}

/*
 Enter the no. of processes : 3
Enter arrival time and burst time for each process :
1
3
2
4
1
2
4
5
*/
