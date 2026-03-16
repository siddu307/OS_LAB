#include <stdio.h>
#include <stdlib.h>

struct process {
    int pid, at, bt, ct, tat, wt, rt;
};

struct Queue {
    int items[100];
    int front, rear;
};

void enqueue(struct Queue *q, int value) {
    q->items[++q->rear] = value;
}

int dequeue(struct Queue *q) {
    return q->items[++q->front];
}

int isEmpty(struct Queue *q) {
    return q->front == q->rear;
}

void roundRobin(struct process p[], int n, int tq) {
    struct Queue q;
    q.front = q.rear = -1;

    int time = 0, completed = 0;
    int sum_tat = 0, sum_wt = 0;
    int visited[n];
    int gantt_pid[100], gantt_start[100], gantt_end[100], gantt_count = 0;

    for (int i = 0; i < n; i++) visited[i] = 0;
    for (int i = 0; i < n; i++) {
        if (p[i].at == 0) {
            enqueue(&q, i);
            visited[i] = 1;
        }
    }

    while (completed < n) {
        if (!isEmpty(&q)) {
            int idx = dequeue(&q);
            gantt_pid[gantt_count] = p[idx].pid;
            gantt_start[gantt_count] = time;

            if (p[idx].rt > tq) {
                time += tq;
                p[idx].rt -= tq;
            } else {
                time += p[idx].rt;
                p[idx].rt = 0;
                p[idx].ct = time;
                completed++;
            }

            gantt_end[gantt_count] = time;
            gantt_count++;

            for (int i = 0; i < n; i++) {
                if (p[i].at <= time && !visited[i]) {
                    enqueue(&q, i);
                    visited[i] = 1;
                }
            }

            if (p[idx].rt > 0) {
                enqueue(&q, idx);
            }
        } else {
            time++;
            for (int i = 0; i < n; i++) {
                if (p[i].at <= time && !visited[i]) {
                    enqueue(&q, i);
                    visited[i] = 1;
                }
            }
        }
    }

    printf("\nProcess Table:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        sum_tat += p[i].tat;
        sum_wt += p[i].wt;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    double avgtat = (double)sum_tat / n;
    double avgwt = (double)sum_wt / n;
    printf("Average TAT = %.2f\n", avgtat);
    printf("Average WT = %.2f\n", avgwt);

    printf("\nGantt Chart:\n");
    for (int i = 0; i < gantt_count; i++) {
        printf("| P%d (%d-%d) ", gantt_pid[i], gantt_start[i], gantt_end[i]);
    }
    printf("|\n");
}

int main() {
    int n, tq;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &tq);

    struct process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;
    }

    roundRobin(p, n, tq);
    return 0;
}