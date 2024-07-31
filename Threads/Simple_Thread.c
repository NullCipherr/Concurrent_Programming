#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Desafio: Threads
// Objetivo: Crie 3 threads, onde cada thread imprime seu próprio ID.
// exemplo: thread 1 imprime "Olá eu sou a thread 1", thread 2 imprime "Olá eu sou a thread 2", thread 3 imprime "Olá eu sou a thread 3".

#define NUM_THREADS 3

void *printID(void *arg)
{
    int id = *(int *)arg;
    printf("Thread %d: Olá eu sou a thread %d \n", id, id);
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_args[i] = i + 1;
        pthread_create(&threads[i], NULL, printID, (void *)&thread_args[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}