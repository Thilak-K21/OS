#include<stdio.h>

struct Process
{
    int at,bt,ct,tat,id,wt,queue;
};

int main()
{
    int n, quantum1;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process ps[n];
    int bt_remaining[n];

    for (int i = 0; i < n; i++) {
        ps[i].id = i + 1;
        printf("Enter Arrival Time, Burst Time, and Queue (1: RR, 2: FCFS) for Process %d: ", i + 1);
        scanf("%d %d %d", &ps[i].at, &ps[i].bt, &ps[i].queue);
        bt_remaining[i] = ps[i].bt;
    }

    printf("Enter the quantum for Round Robin(Queue 1) : ");
    scanf("%d", &quantum1);

    int currentTime=0,completed=0;
    float totalTAT=0,totalWT=0;

    while(completed<n)
    {
        int done=1;
        for(int i=0;i<n;i++)
        {
            if(ps[i].queue==1 && ps[i].at<=currentTime && bt_remaining[i]>0)
            {
                done=0;
                if(bt_remaining[i]>quantum1)
                {
                    currentTime+=quantum1;
                    bt_remaining[i]-=quantum1;
                }
                else{
                    currentTime+=quantum1;
                    bt_remaining[i]=0;
                    ps[i].ct=currentTime;
                    ps[i].tat=ps[i].ct-ps[i].at;
                    ps[i].wt=ps[i].tat-ps[i].bt;
                    totalTAT+=ps[i].tat;
                    totalWT+=ps[i].wt;
                    completed++;
                }
            }
        }
        if(done)
        {
            break;
        }
    }

    while(completed<n)
    {
        int done = 1;
        for (int i = 0; i < n; i++)
            {
            if (ps[i].queue == 2 && bt_remaining[i] > 0 && ps[i].at <= currentTime)
             {
                done = 0;
                currentTime += bt_remaining[i];
                bt_remaining[i] = 0;
                ps[i].ct = currentTime;
                ps[i].tat = ps[i].ct - ps[i].at;
                ps[i].wt = ps[i].tat - ps[i].bt;
                totalTAT += ps[i].tat;
                totalWT += ps[i].wt;
                completed++;
            }
        }
        if (done){break;}
    }

     printf("\nProcess\tAT\tBT\tQueue\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               ps[i].id, ps[i].at, ps[i].bt, ps[i].queue, ps[i].ct, ps[i].tat, ps[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);
    printf("Average Waiting Time: %.2f\n", totalWT / n);

    return 0;
}
