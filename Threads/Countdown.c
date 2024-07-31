#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Desafio: Contagem Regressiva
// Objetivo : Crie três threads, onde cada uma imprime uma contagem regressiva de 10 a 1.
// Exemplo: 10, 9, 8, 7, 6, 5, 4, 3, 2, 1

#define NUM_THREADS 3

void *countdown(void *arg)
{
    int number = *(int *)arg;
    for (int i = number; i >= 1; i--)
    {
        printf("%d\n", i);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int numbers[NUM_THREADS] = {10, 5, 15};

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, countdown, (void *)&numbers[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}