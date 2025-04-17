#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 3  // Number of philosophers

sem_t forks[N];         // One semaphore per fork
sem_t mutex;            // Global mutex to avoid deadlock

void *philosopher(void *num) {
    int id = *(int *)num;

    while (1) {
        printf("Philosopher %d is thinking...\n", id);
        sleep(1);  // Simulate thinking

        sem_wait(&mutex);           // Request permission to pick up forks
        sem_wait(&forks[id]);       // Pick up left fork
        sem_wait(&forks[(id + 1) % N]); // Pick up right fork
        sem_post(&mutex);           // Release global lock

        printf("Philosopher %d is eating...\n", id);
        sleep(2);  // Simulate eating

        sem_post(&forks[id]);       // Put down left fork
        sem_post(&forks[(id + 1) % N]); // Put down right fork

        printf("Philosopher %d finished eating and put down forks.\n", id);
        sleep(1);
    }


}

int main() {
    pthread_t tid[N];
    int ids[N];

    // Initialize semaphores
    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);  // One fork available
    }
    sem_init(&mutex, 0, 1);  // Binary semaphore

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&tid[i], NULL, philosopher, &ids[i]);
    }

    // Join threads (optional, since they run forever)
    for (int i = 0; i < N; i++) {
        pthread_join(tid[i], NULL);
    }

    // Destroy semaphores (not reached here)
    for (int i = 0; i < N; i++) {
        sem_destroy(&forks[i]);
    }
    sem_destroy(&mutex);

    return 0;
}
