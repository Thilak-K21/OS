#include <stdio.h>

#define MAX_TASKS 10
#define MAX_JOBS 1000

typedef struct {
    int id, capacity, deadline, period;
} Task;

typedef struct {
    int task_id, remaining_time, absolute_deadline, release_time, completed;
} Job;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}

int lcm_of_periods(Task tasks[], int k) {
    int l = tasks[0].period;
    for (int i = 1; i < k; i++) {
        l = lcm(l, tasks[i].period);
    }
    return l;
}

int main() {
    int k, hyperperiod;
    Task tasks[MAX_TASKS];
    Job jobs[MAX_JOBS];

    printf("Enter the number of tasks (max %d): ", MAX_TASKS);
    scanf("%d", &k);

    for (int i = 0; i < k; i++) {
        tasks[i].id = i + 1;
        printf("Enter capacity, deadline, and period for task %d: ", tasks[i].id);
        scanf("%d %d %d", &tasks[i].capacity, &tasks[i].deadline, &tasks[i].period);
    }

    hyperperiod = lcm_of_periods(tasks, k);
    printf("\nLCM (Hyperperiod) of periods: %d\n", hyperperiod);

    int job_count = 0;
    for (int i = 0; i < k; i++) {
        for (int release_time = 0; release_time < hyperperiod; release_time += tasks[i].period) {
            jobs[job_count++] = (Job){tasks[i].id, tasks[i].capacity, release_time + tasks[i].deadline, release_time, 0};
        }
    }

    printf("\nTime : Running Task\n");

    for (int time = 0; time < hyperperiod; time++) {
        int selected_job_index = -1, earliest_deadline = 1e6;

        for (int j = 0; j < job_count; j++) {
            if (!jobs[j].completed && jobs[j].release_time <= time && jobs[j].remaining_time > 0) {
                if (jobs[j].absolute_deadline < earliest_deadline) {
                    earliest_deadline = jobs[j].absolute_deadline;
                    selected_job_index = j;
                }
            }
        }

        if (selected_job_index == -1) {
            printf("%4d : Idle\n", time);
        } else {
            jobs[selected_job_index].remaining_time--;
            printf("%4d : Task %d\n", time, jobs[selected_job_index].task_id);
            if (jobs[selected_job_index].remaining_time == 0) {
                if (time + 1 > jobs[selected_job_index].absolute_deadline) {
                    printf("      --> Task %d missed its deadline at time %d\n", jobs[selected_job_index].task_id, time + 1);
                }
                jobs[selected_job_index].completed = 1;
            }
        }
    }

    return 0;
}
