#include <stdio.h>

void findWaitingTime(int processes[], int n, int bt[], int wt[], int pr[]) {
    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
    }
}

void findTurnaroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

void findAverageTime(int processes[], int n, int bt[], int pr[]) {
    int wt[n], tat[n];
    findWaitingTime(processes, n, bt, wt, pr);
    findTurnaroundTime(processes, n, bt, wt, tat);

    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("Process\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], bt[i], pr[i], wt[i], tat[i]);
    }

    printf("Average waiting time: %.2f\n", (float)total_wt / n);
    printf("Average turnaround time: %.2f\n", (float)total_tat / n);
}

void sortProcesses(int processes[], int bt[], int pr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (pr[i] > pr[j]) {
                int temp = pr[i];
                pr[i] = pr[j];
                pr[j] = temp;
                
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
                
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

int main() {
    int processes[] = {1, 2, 3, 4};
    int burst_time[] = {6, 8, 7, 3};
    int priority[] = {2, 1, 4, 3};
    int n = sizeof(processes) / sizeof(processes[0]);

    sortProcesses(processes, burst_time, priority, n);
    findAverageTime(processes, n, burst_time, priority);
    return 0;
}

// Process    Burst Time    Priority    Waiting Time    Turnaround Time
// 2          8             1           0               8
// 1          6             2           8               14
// 4          3             3           14              17
// 3          7             4           17              24
// Average waiting time: 9.75
// Average turnaround time: 15.75

