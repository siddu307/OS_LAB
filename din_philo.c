#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t chopstick[N];
pthread_mutex_t mutex;

void *philosopher(void *num) {
    int id = *(int *)num;

    while (1) {
        pthread_mutex_lock(&mutex);
        printf("Philosopher %d status: THINKING\n", id);
        pthread_mutex_unlock(&mutex);

        sleep(1);

        pthread_mutex_lock(&mutex);
        printf("Philosopher %d status: WAITING\n", id);
        pthread_mutex_unlock(&mutex);

        sem_wait(&chopstick[id]);
        sem_wait(&chopstick[(id + 1) % N]);

        pthread_mutex_lock(&mutex);
        printf("Philosopher %d status: EATING\n", id);
        pthread_mutex_unlock(&mutex);

        sleep(2);

        sem_post(&chopstick[id]);
        sem_post(&chopstick[(id + 1) % N]);
    }
}

int main() {
    pthread_t tid[N];
    int i, ids[N];

    pthread_mutex_init(&mutex, NULL);

    for (i = 0; i < N; i++)
        sem_init(&chopstick[i], 0, 1);

    for (i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&tid[i], NULL, philosopher, &ids[i]);
    }

    for (i = 0; i < N; i++)
        pthread_join(tid[i], NULL);

    return 0;
}
