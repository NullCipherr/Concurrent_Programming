// 1. Deadlock
//
// Deadlock é uma situação em que duas ou mais threads ficam bloqueadas para sempre, esperando uma pela outra para liberar recursos.
// Isso ocorre quando duas threads tentam adquirir dois locks em ordens diferentes.
//
// 2. Exemplo
// No exemplo abaixo, thread1 e thread2 entram em um deadlock porque cada uma bloqueia um mutex e, em seguida, tenta bloquear o segundo mutex que já está bloqueado pela outra thread.

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
    pthread_mutex_lock(&lock1);
    sleep(1); // Simula algum processamento
    pthread_mutex_lock(&lock2);

    printf("Thread 1 acquired both locks\n");

    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);

    pthread_exit(NULL);
}

/*
 * Função executada pela thread 2
 */
void *thread2_func(void *arg)
{
    pthread_mutex_lock(&lock2);
    sleep(1); // Simula algum processamento
    pthread_mutex_lock(&lock1);

    printf("Thread 2 acquired both locks\n");

    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);

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