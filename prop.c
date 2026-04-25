#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int id;
    int burst;
    int shares;
} Process;

void scheduling_proportional_share(Process p[], int n, int total_shares, int total_burst) {
    srand(time(NULL));
    int time_elapsed = 0;

    printf("\nGantt Chart (Total Time: %d):\n|", total_burst);
    while (time_elapsed < total_burst) {
        int lottery = (rand() % total_shares) + 1;
        int accumulated = 0;

        for (int i = 0; i < n; i++) {
            if (p[i].burst > 0) {
                accumulated += p[i].shares;
                if (lottery <= accumulated) {
                    printf(" P%d |", p[i].id);
                    p[i].burst--;
                    time_elapsed++;
                    break;
                }
            }
        }
    }

    printf("\n0");
    for (int i = 1; i <= time_elapsed; i++) {
        printf("   %2d", i);
    }
    printf("\n");
}

int main() {
    int n, total_shares = 0, total_burst = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("P%d [Burst Shares]: ", i + 1);
        scanf("%d %d", &p[i].burst, &p[i].shares);
        total_shares += p[i].shares;
        total_burst += p[i].burst;
    }

    scheduling_proportional_share(p, n, total_shares, total_burst);
    return 0;
}