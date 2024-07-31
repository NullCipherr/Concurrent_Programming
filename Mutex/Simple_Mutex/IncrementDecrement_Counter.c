// 1. Mutex
//
// Os mutexes são utilizados para sincronizar o acesso a recursos compartilhados entre threads, garantindo que apenas uma thread por vez possa acessar o recurso, evitando condições de corrida.
//
// 2. Exercicio
//
// Incremento e Decremento de um contador
// Implemente um algoritmo onde metade das threads incremente o contador e a outra metade decremente o contador, utilizando mutex para garantir a consistência do contador.
// O programa deve imprimir o valor final do contador.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10         // Número de threads
int counter = 0;               // Contador
pthread_mutex_t counter_mutex; // Contador mutex

/*
 * Função que incrementa o contador
 * @param threadid: identificador da thread
 * @return void
 */
void *increment_counter(void *thread_id)
{
    long t_id = (long)thread_id;                // Identificador da thread
    printf("Thread #%ld iniciando...\n", t_id); // Mensagem de debug

    pthread_mutex_lock(&counter_mutex);                                    // Bloqueia o mutex
    counter++;                                                             // Incrementa o contador
    printf("Thread #%ld incrementou o contador para %d\n", t_id, counter); // Mensagem de debug
    pthread_mutex_unlock(&counter_mutex);                                  // Desbloqueia o mutexs

    pthread_exit(NULL); // Finaliza a thread
}

void *decrement_counter(void *thread_id)
{
    long t_id = (long)thread_id;               // Identificador da thread
    printf("Thread #%ld starting...\n", t_id); // Mensagem de debug

    pthread_mutex_lock(&counter_mutex);                                    // Bloqueia o mutex
    counter--;                                                             // Incrementa o contador
    printf("Thread #%ld decrementou o contador para %d\n", t_id, counter); // Mensagem de debug
    pthread_mutex_unlock(&counter_mutex);                                  // Desbloqueia o mutexs

    pthread_exit(NULL); // Finaliza a thread
}

int main()
{
    pthread_t threads[NUM_THREADS]; // Vetor de threads
    int rc;                         // Variável de retorno
    long t;                         // Variável de controle

    // Inicialização do mutex
    pthread_mutex_init(&counter_mutex, NULL);

    // Criação das threads
    for (t = 0; t < NUM_THREADS; t++)
    {
        // Verifique se a thread está na primeira metade
        if (t < (NUM_THREADS / 2))
        {
            printf("Creating Increment thread #%ld\n", t);                        // Mensagem de debug
            rc = pthread_create(&threads[t], NULL, increment_counter, (void *)t); // Criação da thread
        }
        // Caso contrário, crie uma thread de decremento
        else
        {
            printf("Creating Decrement thread #%ld\n", t);                        // Mensagem de debug
            rc = pthread_create(&threads[t], NULL, decrement_counter, (void *)t); // Criação da thread
        }

        // Verificação de erro
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    // Aguarda o término das threads
    for (t = 0; t < NUM_THREADS; t++)
    {
        pthread_join(threads[t], NULL);
    }

    printf("Final counter value: %d\n", counter); // Imprime o valor final do contador

    pthread_mutex_destroy(&counter_mutex); // Destroi o mutex
    pthread_exit(NULL);                    // Finaliza a thread
}