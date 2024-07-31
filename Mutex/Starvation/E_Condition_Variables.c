// Exercicio - Prevenir Starvation com Variáveis de Condição
//
// Modifique o exemplo de acesso a recurso compartilhado para usar variáveis de condição de modo a prevenir starvation, garantindo que todas as threads tenham acesso ao recurso de forma justa.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10 // Número de threads
#define TIME 500000    // 500ms

pthread_mutex_t res_mutex; // Mutex
pthread_cond_t cond;       // Variável de condição

int waiting_t = 0; // Número de threads esperando
int turn = 0;      // Turno da thread

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
        pthread_mutex_lock(&res_mutex); // Bloqueia o mutex
        waiting_t++;                    // Incrementa o número de threads esperando

        // Enquanto não for o turno da thread, espera
        while (thread_id != turn)
        {
            pthread_cond_wait(&cond, &res_mutex); // Aguarda a liberação do recurso
        }

        printf("Thread #%d em execução\n", thread_id);
        usleep(TIME); // Simula um trabalho

        turn = (turn + 1) % NUM_THREADS; // Atualiza o turno
        waiting_t--;                     // Decrementa o número de threads esperando

        pthread_cond_broadcast(&cond);    // Libera todas as threads
        pthread_mutex_unlock(&res_mutex); // Desbloqueia o mutex
        usleep(TIME);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int threads_id[NUM_THREADS];

    pthread_mutex_init(&res_mutex, NULL); // Inicializa o mutex
    pthread_cond_init(&cond, NULL);       // Inicializa a variável de condição

    for (int i = 0; i < NUM_THREADS; i++)
    {
        threads_id[i] = i;
        pthread_create(&threads[i], NULL, thread_task, (void *)&threads_id[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&res_mutex); // Destroi o mutex
    pthread_cond_destroy(&cond);       // Destroi a variável de condição

    return 0;
}