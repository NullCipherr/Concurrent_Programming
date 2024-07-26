// 1. Prevenção de Deadlocks
//
// Para prevenir deadlocks, Existem várias estratégias, incluindo:
//  1. Ordenação Consistente dos Recursos : Garanta que todas as threads bloqueiem múltiplos mutexes na mesma ordem.
//  2. Evitar Bloqueio Aninhado : Reduza ao mínimo a necessidade de bloqueios aninhados, onde uma thread precisa bloquear mais de um mutex ao mesmo tempo.
//  3. Usar pthread_mutex_trylock : Utilize pthread_mutex_trylock para tentar bloquear o mutex sem bloquear a thread indefinidamente.
//
// 2. Exercício
// Implemente um algoritmo ques previna o deadlock do código 'Deadlock.c'
// O algoritmo deve garantir que as threads adquiram os locks na mesma ordem, evitando o deadlock.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t lock1; // Mutex 1
pthread_mutex_t lock2; // Mutex 2

/*
 * Função executada pela thread 1
 */
void *thread1_func(void *arg)
{
    while (1) // Loop infinito
    {
        if (pthread_mutex_trylock(&lock1) == 0) // Tenta bloquear o mutex 1
        {
            sleep(1);                               // Simula algum processamento
            if (pthread_mutex_trylock(&lock2) == 0) // Tenta bloquear o mutex 2
            {
                printf("Thread 1 adquiriu ambos os locks\n");
                pthread_mutex_unlock(&lock2); // Desbloqueia o mutex 2
                pthread_mutex_unlock(&lock1); // Desbloqueia o mutex 1
                break;                        // Sai do loop
            }
            else // Se não conseguir bloquear o mutex 2, desbloqueia o mutex 1
            {
                pthread_mutex_unlock(&lock1); // Desbloqueia o mutex 1
            }
        }
        sleep(1);
    }

    pthread_exit(NULL);
}

/*
 * Função executada pela thread 2
 */
void *thread2_func(void *arg)
{
    while (1) // Loop infinito
    {
        if (pthread_mutex_trylock(&lock2) == 0) // Tenta bloquear o mutex 2
        {
            sleep(1);                               // Simula algum processamento
            if (pthread_mutex_trylock(&lock1) == 0) // Tenta bloquear o mutex 1
            {
                printf("Thread 2 adquiriu ambos os locks\n"); // Se conseguir bloquear ambos os mutexes, imprime a mensagem
                pthread_mutex_unlock(&lock1);                 // Desbloqueia o mutex 1
                pthread_mutex_unlock(&lock2);                 // Desbloqueia o mutex 2
                break;                                        // Sai do loop
            }
            else // Se não conseguir bloquear o mutex 1, desbloqueia o mutex 2
            {
                pthread_mutex_unlock(&lock2); // Desbloqueia o mutex 2
            }
        }
        sleep(1);
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t thread1, thread2; // Threads

    pthread_mutex_init(&lock1, NULL); // Inicializa o mutex 1
    pthread_mutex_init(&lock2, NULL); // Inicializa o mutex 2

    pthread_create(&thread1, NULL, thread1_func, NULL); // Cria a thread 1
    pthread_create(&thread2, NULL, thread2_func, NULL); // Cria a thread 2

    pthread_join(thread1, NULL); // Espera a thread 1 terminar
    pthread_join(thread2, NULL); // Espera a thread 2 terminar

    pthread_mutex_destroy(&lock1); // Destroi o mutex 1
    pthread_mutex_destroy(&lock2); // Destroi o mutex 2

    return 0;
}

/*
    Observações:

        Foi utilizado a função pthread_mutex_trylock para tentar bloquear o mutex sem bloquear a thread indefinidamente.
    Dessa forma, a thread tenta bloquear o mutex e, caso não consiga, desbloqueia o mutex anterior e tenta novamente.
    Isso evita o deadlock, pois as threads adquirem os locks na mesma ordem.
*/