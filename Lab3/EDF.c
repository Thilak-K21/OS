#include <stdio.h>

struct Process {
    int id;
    int at;
    int bt;
    int dl;
    int ct;
    int tat;
    int wt;
    int isCompleted;
};

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process ps[n];

    for (int i = 0; i < n; i++) {
        ps[i].id = i + 1;
        printf("Enter Arrival Time, Burst Time, and Deadline for Process %d: ", ps[i].id);
        scanf("%d %d %d", &ps[i].at, &ps[i].bt, &ps[i].dl);
        ps[i].isCompleted = 0;
    }

    int completed = 0, currentTime = 0;
    float totalTAT = 0, totalWT = 0;

    while (completed < n) {
        int idx = -1;
        int earliestDeadline = 1e9;

        for (int i = 0; i < n; i++) {
            if (!ps[i].isCompleted && ps[i].at <= currentTime && ps[i].dl < earliestDeadline) {
                earliestDeadline = ps[i].dl;
                idx = i;
            }
        }

        if (idx != -1) {
            currentTime += ps[idx].bt;
            ps[idx].ct = currentTime;
            ps[idx].tat = ps[idx].ct - ps[idx].at;
            ps[idx].wt = ps[idx].tat - ps[idx].bt;
            ps[idx].isCompleted = 1;
            totalTAT += ps[idx].tat;
            totalWT += ps[idx].wt;
            completed++;
        } else {
            currentTime++;
        }
    }

    printf("\nProcess\tAT\tBT\tDL\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               ps[i].id, ps[i].at, ps[i].bt, ps[i].dl, ps[i].ct, ps[i].tat, ps[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);
    printf("Average Waiting Time: %.2f\n", totalWT / n);

    return 0;
}
