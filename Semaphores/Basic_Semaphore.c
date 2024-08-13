#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 4

// Definindo um semáforo
sem_t semaphore;

void *threadWork(void *arg)
{
    // Espera pelo semáforo
    sem_wait(&semaphore);

    // Seção crítica
    printf("Thread %d está na seção crítica\n", *(int *)arg);

    // Simula algum trabalho : 1 segundo
    sleep(1);

    // Libera o semáforo
    sem_post(&semaphore);

    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int thread_id[NUM_THREADS] = {1, 2, 3, 4};

    printf("Iniciando o programa...\n");

    // Inicializa o semáforo com o valor 1 (Semáforo binário) -> Mutex
    sem_init(&semaphore, 0, 1);

    // Cria as threads
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, threadWork, &thread_id[i]);
    }

    // Espera as threads terminarem
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Destrói o semáforo
    sem_destroy(&semaphore);

    printf("Finalizando o programa...\n");

    return 0;
}