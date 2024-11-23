#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int pid;
    int burst_time;
    int arrival_time;
    int remaining_time;
    int priority;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    bool completed;
} Process;

void priority_preemptive(Process processes[], int n) {
    int current_time = 0;
    int completed = 0;

    while (completed < n) {
        int idx = -1;
        int max_priority = -1; // Initialize to a low value for maximum priority selection.

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && 
                !processes[i].completed && 
                processes[i].priority > max_priority) { // Select higher priority.
                max_priority = processes[i].priority;
                idx = i;
            }
        }

        if (idx != -1) {
            processes[idx].remaining_time--;
            current_time++;

            if (processes[idx].remaining_time == 0) {
                processes[idx].completion_time = current_time;
                processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
                processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
                processes[idx].completed = true;
                completed++;
            }
        } else {
            current_time++;
        }
    }
}

void print_table(Process processes[], int n) {
    printf("\nPID\tBurst Time\tArrival Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
            processes[i].pid,
            processes[i].burst_time,
            processes[i].arrival_time,
            processes[i].priority,
            processes[i].completion_time,
            processes[i].turnaround_time,
            processes[i].waiting_time);
    }
}

void calculate_avg_times(Process processes[], int n) {
    float total_tat = 0, total_wt = 0;
    for (int i = 0; i < n; i++) {
        total_tat += processes[i].turnaround_time;
        total_wt += processes[i].waiting_time;
    }
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
        processes[i].pid = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completed = false;
    }

    priority_preemptive(processes, n);
    print_table(processes, n);
    calculate_avg_times(processes, n);

    return 0;
}
// High number high priority
/*
Enter the number of processes: 4
Enter arrival time, burst time, and priority for process 1: 0 5 10
Enter arrival time, burst time, and priority for process 2: 1 4 20
Enter arrival time, burst time, and priority for process 3: 2 2 30
Enter arrival time, burst time, and priority for process 4: 4 1 40
*/
