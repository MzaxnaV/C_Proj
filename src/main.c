// C program to demonstrate working of Semaphores
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem;

typedef struct thread_data {
    size_t id;
    size_t* data;
} thread_data;


void* thread(void* arg)
{
    thread_data* id = arg;
    printf("Inside Thread %ld\n", id->id);
    sem_wait(&sem);
    printf("Thread data: {%ld, %ld}\n", id->id, *(id->data));
    sleep(1);
    sem_post(&sem);
}

int main()
{
    sem_init(&sem, 0, 1);

    pthread_t threads[10];
    thread_data td[10];

    for (size_t i = 0; i < 10; ++i) {
        thread_data d = {i, &i};
        td[i] = d;
        pthread_create(&threads[i], NULL, thread, (void*)(td + i));
    }

    for (size_t i = 0; i < 10; ++i) {
        pthread_join(threads[i], NULL);
    }

    sleep(3);

    sem_destroy(&sem);
}
