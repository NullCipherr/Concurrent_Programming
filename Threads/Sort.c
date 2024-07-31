#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Desafio: Ordenação de Números
// Objetivo: Crie três threads, onde cada uma ordena um conjunto de números diferentes e imprime os números ordenados.
// exemplo: {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, {1, 3, 5, 7, 9, 2, 4, 6, 8, 10}, {5, 4, 3, 2, 1, 10, 9, 8, 7, 6}.
// Saída esperada: 1 2 3 4 5 6 7 8 9 10, 1 2 3 4 5 6 7 8 9 10, 1 2 3 4 5 6 7 8 9 10.

#define NUM_THREADS 3

void *sort(void *arg)
{
    int *numbers = (int *)arg;
    int temp;
    for (int i = 0; i < 10; i++)
    {
        for (int j = i + 1; j < 10; j++)
        {
            if (numbers[i] > numbers[j])
            {
                temp = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = temp;
            }
        }
    }

    for (int i = 0; i < 10; i++)
    {
        printf("%d ", numbers[i]);
    }

    printf("\n");
    pthread_exit(NULL);
}

int main()
{
    pthread_t thread[NUM_THREADS];
    int numbers[NUM_THREADS][10] = {
        {10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
        {1, 3, 5, 7, 9, 2, 4, 6, 8, 10},
        {5, 4, 3, 2, 1, 10, 9, 8, 7, 6}};

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&thread[i], NULL, sort, (void *)numbers[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(thread[i], NULL);
    }

    return 0;
}