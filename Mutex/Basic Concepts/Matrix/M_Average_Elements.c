// Média de Elementos de uma Matriz
//
// Descrição : Escreva um programa que cria várias threads para calcular a média de todos os elementos de uma matriz.
// Use um mutex para garantir que a soma e a contagem de elementos sejam atualizadas corretamente.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4

#define ROWS 4
#define COLS 4

int matriz[ROWS][COLS] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}};

int sum = 0;
int count = 0;
pthread_mutex_t mutex;

void *sum_matrix(void *arg)
{
    int start = *((int *)arg);
    int end = start + ROWS / NUM_THREADS; // Divide a matriz em partes iguais

    for (int i = start; i < end; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            pthread_mutex_lock(&mutex);
            sum += matriz[i][j];
            count++;
            pthread_mutex_unlock(&mutex);
        }
    }
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_args[i] = i * ROWS / NUM_THREADS;
        pthread_create(&threads[i], NULL, sum_matrix, &thread_args[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    double average = (double)sum / count;
    printf("Média dos elementos da matriz: %.2f\n", average);

    pthread_mutex_destroy(&mutex);

    return 0;
}