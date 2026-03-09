#include<stdio.h>

struct process{
    int pid;
    int at;
    int bt;
    int rt_bt;
    int ct;
    int wt;
    int tat;
    int rt;
};

void sjf_pa(struct process p[],int n){
    int time=0,completed=0,min,index;
    float total_tat=0,total_wt=0,total_rt=0;
    while(completed!=n){
        min=999;
        index=-1;

        for(int i=0;i<n;i++){
            if(p[i].at<=time && p[i].rt_bt>0){
                if(p[i].rt_bt<min){
                    min=p[i].rt_bt;
                    index=i;
                }
                else if(p[i].rt_bt==min){
                    if(p[i].at<p[index].at){
                        index=i;
                    }
                }
            }
        }

        if(index==-1){
            time++;
            continue;
        }

        if(p[index].rt==-1){
            p[index].rt=time-p[index].at;
        }
        p[index].rt_bt--;
        time++;

        if(p[index].rt_bt==0){
            p[index].ct=time;
            p[index].tat=p[index].ct-p[index].at;
            p[index].wt=p[index].tat-p[index].bt;
            completed++;
        }
    }

    for(int i=0;i<n;i++){
        total_wt+=p[i].wt;
        total_tat+=p[i].tat;
        total_rt+=p[i].rt;
    }

    printf("PID\tAT\tBT\tCT\tWT\tTAT\tRT\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].wt,p[i].tat,p[i].rt);
    }

    printf("Average waiting time=%.2f\n",total_wt/n);
    printf("Average turn around time=%.2f\n",total_tat/n);
    printf("Average response time=%.2f\n",total_rt/n);
}

int main(){

    int n;
    printf("enter number of processes:");
    scanf("%d",&n);

    struct process p[n];

    for(int i=0;i<n;i++){
        printf("\nProcess %d\n",i+1);
        p[i].pid=i+1;
        printf("Arrival Time:");
        scanf("%d",&p[i].at);
        printf("Burst Time:");
        scanf("%d",&p[i].bt);
        p[i].rt_bt=p[i].bt;
        p[i].rt=-1;
    }

    sjf_pa(p,n);

    return 0;
}