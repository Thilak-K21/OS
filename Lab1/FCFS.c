#include<stdio.h>
#include<stdbool.h>

int main()
{
    int ps[100],at[100],bt[100],ct[100],tat[100],wt[100],n;
    float totalTAT=0,totalWT=0;
    printf("Enter the number of process to enter : ");
    scanf("%d",&n);

    for(int i=0;i<n;i++)
    {
        printf("\n Enter the arrival time of process [%d] : ",i+1);
        scanf("%d",&at[i]);
    }

    for(int i=0;i<n;i++)
    {
        printf("\n Enter the burst time of process [%d] : ",i+1);
        scanf("%d",&bt[i]);
    }

    int sum=at[0];
    for(int i=0;i<n;i++)
    {
        sum+=bt[i];
        ct[i]=sum;
    }

    for(int i=0;i<n;i++)
    {
        tat[i]=ct[i]-at[i];
        totalTAT+=tat[i];
    }

    for(int i=0;i<n;i++)
    {
        wt[i]=tat[i]-bt[i];
        totalWT+=wt[i];
    }

    printf("\n The average TAT is : %.2f ms",(float)totalTAT/n);
    printf("\n The average WT is : %.2f ms\n\n\n",(float)totalWT/n);

    return 0;
}
