#include <stdio.h>
#include <stdbool.h>

#define P 10
#define R 10

int allocation[P][R], request[P][R], available[R];
int n, m;

void detectDeadlock() {
    bool finish[P];
    int work[R];
    for (int i = 0; i < n; i++) finish[i] = false;
    for (int i = 0; i < m; i++) work[i] = available[i];

    bool deadlock = false;

    for (int count = 0; count < n; count++) {
        bool found = false;
        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                bool canProceed = true;
                for (int r = 0; r < m; r++) {
                    if (request[p][r] > work[r]) {
                        canProceed = false;
                        break;
                    }
                }
                if (canProceed) {
                    for (int r = 0; r < m; r++)
                        work[r] += allocation[p][r];
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) break;
    }

    for (int p = 0; p < n; p++) {
        if (!finish[p]) {
            deadlock = true;
            printf("Process %d is in deadlock.\n", p);
        }
    }

    if (!deadlock)
        printf("No deadlock detected.\n");
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter Request Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &request[i][j]);

    printf("Enter Available Resources (%d):\n", m);
    for (int i = 0; i < m; i++)
        scanf("%d", &available[i]);

    detectDeadlock();
    return 0;
}

