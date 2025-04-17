#include <stdio.h>

struct Process {
    int id;
    int at;
    int bt;
    int rt;
    int ct;
    int tat;
    int wt;
};

int main() {
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process ps[n];
    for (int i = 0; i < n; i++) {
        ps[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &ps[i].at, &ps[i].bt);
        ps[i].rt = ps[i].bt;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    int completed = 0, currentTime = 0;
    float totalTAT = 0, totalWT = 0;

    while (completed < n) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (ps[i].rt > 0 && ps[i].at <= currentTime) {
                done = 0;
                if (ps[i].rt > quantum) {
                    currentTime += quantum;
                    ps[i].rt -= quantum;
                } else {
                    currentTime += ps[i].rt;
                    ps[i].rt = 0;
                    ps[i].ct = currentTime;
                    ps[i].tat = ps[i].ct - ps[i].at;
                    ps[i].wt = ps[i].tat - ps[i].bt;
                    totalTAT += ps[i].tat;
                    totalWT += ps[i].wt;
                    completed++;
                }
            }
        }
        if (done) currentTime++;
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               ps[i].id, ps[i].at, ps[i].bt, ps[i].ct, ps[i].tat, ps[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);
    printf("Average Waiting Time: %.2f\n", totalWT / n);

    return 0;
}
