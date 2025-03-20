#include <stdio.h>
#include <limits.h>

struct Process {
    int id, at, bt, priority, ct, tat, wt;
};

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process ps[n];
    int bt_remaining[n]; 

    for (int i = 0; i < n; i++) {
        ps[i].id = i + 1;
        printf("Enter Arrival Time, Burst Time and Priority for Process %d: ", i + 1);
        scanf("%d %d %d", &ps[i].at, &ps[i].bt, &ps[i].priority);
        bt_remaining[i] = ps[i].bt; 
    }

    int completed = 0, currentTime = 0;
    float totalTAT = 0, totalWT = 0;

    while (completed < n) {
        int min_index = -1;
        int minPriority = INT_MAX;

       
        for (int i = 0; i < n; i++) {
            if (ps[i].at <= currentTime && bt_remaining[i] > 0) {
                if (ps[i].priority < minPriority) {
                    minPriority = ps[i].priority;
                    min_index = i;
                }
            }
        }

        if (min_index != -1) {
            bt_remaining[min_index]--;
            currentTime++;

          
            if (bt_remaining[min_index] == 0) {
                ps[min_index].ct = currentTime;
                ps[min_index].tat = ps[min_index].ct - ps[min_index].at;
                ps[min_index].wt = ps[min_index].tat - ps[min_index].bt;
                totalTAT += ps[min_index].tat;
                totalWT += ps[min_index].wt;
                completed++;
            }
        } else {
            currentTime++;
        }
    }

    printf("\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               ps[i].id, ps[i].at, ps[i].bt, ps[i].priority,
               ps[i].ct, ps[i].tat, ps[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);
    printf("Average Waiting Time: %.2f\n", totalWT / n);

    return 0;
}
