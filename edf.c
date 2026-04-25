#include <stdio.h>

struct Process {
    int id, bt, deadline, period, remaining, next_deadline;
};

void scheduling_edf(struct Process p[], int n) {
    int i, t = 0;
    
    int max_p = 0;
    for(i = 0; i < n; i++) if(p[i].period > max_p) max_p = p[i].period;
    
    int hyper_period = 1;
    int found = 0;
    while(!found) {
        found = 1;
        for(i = 0; i < n; i++) {
            if(hyper_period % p[i].period != 0) {
                found = 0;
                break;
            }
        }
        if(!found) hyper_period++;
    }

    int gantt[1000];
    for(i = 0; i < n; i++) {
        p[i].remaining = 0; 
        p[i].next_deadline = 0;
    }

    for (t = 0; t < hyper_period; t++) {
        for (i = 0; i < n; i++) {
            if (t % p[i].period == 0) {
                p[i].remaining = p[i].bt;
                p[i].next_deadline = t + p[i].deadline;
            }
        }

        int idx = -1;
        int min_deadline = 9999;
        for (i = 0; i < n; i++) {
            if (p[i].remaining > 0) {
                if (p[i].next_deadline < min_deadline) {
                    min_deadline = p[i].next_deadline;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            gantt[t] = p[idx].id;
            p[idx].remaining--;
        } else {
            gantt[t] = 0;
        }
    }

    printf("\nGantt Chart (Hyper-period: %d)\n+", hyper_period);
    for (i = 0; i < hyper_period; i++) printf("-----+");
    printf("\n|");
    for (i = 0; i < hyper_period; i++) {
        if (gantt[i] == 0) printf("Idle |");
        else printf(" P%-2d |", gantt[i]);
    }
    printf("\n+");
    for (i = 0; i < hyper_period; i++) printf("-----+");
    printf("\n0");
    for (i = 1; i <= hyper_period; i++) printf("%6d", i);
    printf("\n");
}

int main() {
    int n, i;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter P%d [Burst, Deadline, Period]: ", i+1);
        scanf("%d %d %d", &p[i].bt, &p[i].deadline, &p[i].period);
    }

    scheduling_edf(p, n);
    return 0;
}