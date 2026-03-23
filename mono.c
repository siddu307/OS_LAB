#include <stdio.h>

struct task {
    int id;
    int cpu;
    int period;
};

void monotonic_scheduling(struct task t[], int n, int max_time) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (t[j].period > t[j + 1].period) {
                struct task temp = t[j];
                t[j] = t[j + 1];
                t[j + 1] = temp;
            }
        }
    }

    int remaining_time[n], next_arrival[n], misses[max_time];
    for (int i = 0; i < n; i++) {
        remaining_time[i] = 0;
        next_arrival[i] = 0;
    }
    for (int i = 0; i < max_time; i++) misses[i] = -1;

    printf("\nGantt Chart Pipeline:\n|");
    for (int time = 0; time < max_time; time++) {
        for (int i = 0; i < n; i++) {
            if (time == next_arrival[i]) {
                if (remaining_time[i] > 0) {
                    misses[time] = t[i].id; 
                }
                remaining_time[i] = t[i].cpu;
                next_arrival[i] += t[i].period;
            }
        }

        int current_task = -1;
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                current_task = i;
                break;
            }
        }

        if (current_task != -1) {
            printf("T%d\t|", t[current_task].id);
            remaining_time[current_task]--;
        } else {
            printf("Idle\t|");
        }
    }

    printf("\n0");
    for (int time = 0; time < max_time; time++) {
        printf("\t%d", time + 1);
    }
    
    printf("\n\nNotifications:");
    int has_misses = 0;
    for (int i = 0; i < max_time; i++) {
        if (misses[i] != -1) {
            printf("\n[Time %d] DEADLINE MISS: Task %d", i, misses[i]);
            has_misses = 1;
        }
    }
    if (!has_misses) printf("\nNo deadlines missed.");
    printf("\n");
}

int main() {
    int n, max_time;
    printf("Enter number of tasks: ");
    scanf("%d", &n);
    printf("Enter simulation time: ");
    scanf("%d", &max_time);

    struct task t[n];
    for (int i = 0; i < n; i++) {
        printf("Task %d (ID CPU Period): ", i + 1);
        scanf("%d %d %d", &t[i].id, &t[i].cpu, &t[i].period);
    }

    monotonic_scheduling(t, n, max_time);
    return 0;
}