// Exercicio - Algoritmo de Escalonamento Justo
//
// Implemente um algoritmo de escalonamento Round-Robin para garantir que todas as threads recebam tempo de CPU de forma equitativa.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10 // Número de threads
#define TIME_MS 500000 // 500ms

/*
 * Função executada pela thread
 * @param arg: argumento passado para a thread
 * @return void
 */
void *thread_task(void *arg)
{
    int thread_id = *((int *)arg); // Identificador da thread

    // Loop infinito
    while (1)
    {
        printf("Thread #%d em execução\n", thread_id);
        usleep(TIME_MS); // Simula um trabalho
    }
    pthread_exit(NULL);
}

/*
 * Função principal
 */
int main()
{
    pthread_t threads[NUM_THREADS]; // Vetor de threads
    int threads_id[NUM_THREADS];    // Vetor de identificadores de threads

    for (int i = 0; i < NUM_THREADS; i++)
    {
        threads_id[i] = i;
        pthread_create(&threads[i], NULL, thread_task, (void *)&threads_id[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}