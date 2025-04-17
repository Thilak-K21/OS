#include <stdio.h>
#include <math.h>

typedef struct {
    int pid;
    int period;     
    int burst;      
    int remaining;  
} Task;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

int findHyperPeriod(Task tasks[], int n) {
    int hyper = tasks[0].period;
    for (int i = 1; i < n; i++) {
        hyper = lcm(hyper, tasks[i].period);
    }
    return hyper;
}

void sortByPeriod(Task tasks[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (tasks[i].period > tasks[j].period) {
                Task temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
        tasks[i].remaining = tasks[i].burst;
    }
}

// Function to calculate CPU utilization
float calculateCPUUtilization(Task tasks[], int n) {
    float utilization = 0.0;
    for (int i = 0; i < n; i++) {
        utilization += (float)tasks[i].burst / tasks[i].period;
    }
    return utilization;
}

// Function to check if the system is schedulable
int isSchedulable(Task tasks[], int n) {
    float utilization = calculateCPUUtilization(tasks, n);
    // Schedulability bound for RMS
    float threshold = n * (pow(2, 1.0 / n) - 1);
    
    printf("CPU Utilization: %.2f\n", utilization);
    printf("Schedulability Threshold: %.2f\n", threshold);
    
    if (utilization <= threshold) {
        return 1;  // System is schedulable
    } else {
        return 0;  // System is not schedulable
    }
}

void rateMonotonic(Task tasks[], int n, int sim_time) {
    printf("\nRate-Monotonic Scheduling:\n");
    printf("Time\tTask\n");

    sortByPeriod(tasks, n);

    for (int time = 0; time < sim_time; time++) {
        int scheduled = -1;

        for (int i = 0; i < n; i++) {
            if (time % tasks[i].period == 0) {
                tasks[i].remaining = tasks[i].burst;
            }
        }

        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining > 0) {
                scheduled = i;
                break;
            }
        }

        if (scheduled != -1) {
            tasks[scheduled].remaining--;
            printf("%d\tT%d\n", time, tasks[scheduled].pid);
        } else {
            printf("%d\tIdle\n", time);
        }
    }
}

int main() {
    int n;
    printf("Enter number of tasks: ");
    scanf("%d", &n);

    Task tasks[n];
    for (int i = 0; i < n; i++) {
        tasks[i].pid = i + 1;
        printf("Enter period and burst time for task T%d: ", i + 1);
        scanf("%d %d", &tasks[i].period, &tasks[i].burst);
    }

    // Check schedulability before proceeding
    if (!isSchedulable(tasks, n)) {
        printf("The task set is not schedulable under Rate-Monotonic Scheduling.\n");
        return 0;
    }

    int sim_time = findHyperPeriod(tasks, n);
    printf("Simulation will run for %d units (LCM of periods)\n", sim_time);

    rateMonotonic(tasks, n, sim_time);

    return 0;
}
