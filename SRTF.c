#include<stdio.h>
#include<stdbool.h>
#include<limits.h>

struct process_struct {
  int pid, at, bt, ct, wt, tat, start_time;
} ps[100];

int main() {
    int n;
    float bt_remaining[100];
    bool is_completed[100] = {false};
    int current_time = 0, completed = 0;
    float sum_tat = 0, sum_wt = 0;
    int prev = 0;

    printf("Enter total number of processes: ");
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        printf("\nEnter Process %d Arrival Time: ", i);
        scanf("%d", &ps[i].at);
        ps[i].pid = i;
    }
    
    for (int i = 0; i < n; i++) {
        printf("\nEnter Process %d Burst Time: ", i);
        scanf("%d", &ps[i].bt);
        bt_remaining[i] = ps[i].bt;
    }
   
    while (completed != n) {
        int min_index = -1, minimum = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (ps[i].at <= current_time && !is_completed[i] && bt_remaining[i] < minimum) {
                minimum = bt_remaining[i];
                min_index = i;
            }
        }
  
        if (min_index == -1) {
            current_time++;
        } else {
            if (bt_remaining[min_index] == ps[min_index].bt) {
                ps[min_index].start_time = current_time;
            }
            bt_remaining[min_index]--;
            current_time++;
            prev = current_time;
            if (bt_remaining[min_index] == 0) {
                ps[min_index].ct = current_time;
                ps[min_index].tat = ps[min_index].ct - ps[min_index].at;
                ps[min_index].wt = ps[min_index].tat - ps[min_index].bt;
                sum_tat += ps[min_index].tat;
                sum_wt += ps[min_index].wt;
                completed++;
                is_completed[min_index] = true;
            }
        }
    }

    printf("\nAverage Turnaround Time = %f", sum_tat / n);
    printf("\nAverage Waiting Time = %f\n", sum_wt / n);
    
    return 0;
}
