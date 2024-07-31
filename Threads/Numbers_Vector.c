#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Desafio: Preencher Vetor
// Objetivo: Preencher um vetor de 100 posições com números aleatórios
// 1. Criar um vetor de 3000 posições
// 2. Preencher o vetor com números aleatórios
// 3. Exibir o vetor

#define NUM_THREADS 4
#define VECTOR_SIZE 3000

int vector[VECTOR_SIZE];

void *preencherVetor(void *ptr)
{
    int id = (int)(long long)ptr;
    int start = (id - 1) * (VECTOR_SIZE / NUM_THREADS);
    int end = start + (VECTOR_SIZE / NUM_THREADS);

    for (int i = start; i < end; i++)
    {
        vector[i] = rand() % 100;
    }

    pthread_exit(NULL);
}

int main(void)
{
    pthread_t threads[NUM_THREADS];
    int iret[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++)
    {
        iret[i] = pthread_create(&threads[i], NULL, preencherVetor, (void *)(long long)i + 1);
        if (iret[i])
        {
            printf("Erro ao criar a thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < VECTOR_SIZE; i++)
    {
        printf("%d ", vector[i]);
    }

    exit(EXIT_SUCCESS);
}