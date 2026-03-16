#include <stdio.h>

#define MAX 100

struct process {
    int pid, at, bt, type, ct, tat, wt, start;
};

void sortByArrival(struct process q[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (q[i].at > q[j].at) {
                struct process temp = q[i];
                q[i] = q[j];
                q[j] = temp;
            }
        }
    }
}

int executeQueue(struct process q[], int n, int time) {
    for (int i = 0; i < n; i++) {
        if (time < q[i].at) time = q[i].at;
        q[i].start = time;
        time += q[i].bt;
        q[i].ct = time;
        q[i].tat = q[i].ct - q[i].at;
        q[i].wt = q[i].tat - q[i].bt;
    }
    return time;
}

void printGanttChart(struct process sysQ[], int sysCount, struct process userQ[], int userCount) {
    printf("\nGantt Chart:\n");
    for (int i = 0; i < sysCount; i++) {
        printf("| P%d (%d-%d) ", sysQ[i].pid, sysQ[i].start, sysQ[i].ct);
    }
    for (int i = 0; i < userCount; i++) {
        printf("| P%d (%d-%d) ", userQ[i].pid, userQ[i].start, userQ[i].ct);
    }
    printf("|\n");
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[MAX], systemQ[MAX], userQ[MAX];
    int sysCount = 0, userCount = 0;

    printf("Enter PID AT BT TYPE (0=System,1=User):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &p[i].pid, &p[i].at, &p[i].bt, &p[i].type);
        if (p[i].type == 0) systemQ[sysCount++] = p[i];
        else userQ[userCount++] = p[i];
    }

    sortByArrival(systemQ, sysCount);
    sortByArrival(userQ, userCount);

    int time = 0;
    time = executeQueue(systemQ, sysCount, time);
    time = executeQueue(userQ, userCount, time);

    printf("\nProcess Table:\n");
    printf("PID\tAT\tBT\tTYPE\tCT\tTAT\tWT\n");
    for (int i = 0; i < sysCount; i++) {
        printf("%d\t%d\t%d\tSys\t%d\t%d\t%d\n",
               systemQ[i].pid, systemQ[i].at, systemQ[i].bt,
               systemQ[i].ct, systemQ[i].tat, systemQ[i].wt);
    }
    for (int i = 0; i < userCount; i++) {
        printf("%d\t%d\t%d\tUser\t%d\t%d\t%d\n",
               userQ[i].pid, userQ[i].at, userQ[i].bt,
               userQ[i].ct, userQ[i].tat, userQ[i].wt);
    }

    printGanttChart(systemQ, sysCount, userQ, userCount);

    return 0;
}