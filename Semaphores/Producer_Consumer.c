// Problema do Produtor e Consumidor
//
// Neste problema, um produtor gera itens e os coloca em um buffer compartilhado, enquanto um consumidor remove itens do buffer.

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

#define BUFFER_SIZE 10
int buffer[BUFFER_SIZE];

int entrada = 0; // Posição de entrada
int saida = 0;   // Posição de saída

sem_t mutex, items, spaces; // Semáforos: mutex, items e spaces

void *producer(void *arg)
{
    int item = 0; // Item a ser produzido

    while (1)
    {
        sem_wait(&spaces); // Decrementa o semáforo spaces
        sem_wait(&mutex);  // Decrementa o semáforo mutex

        buffer[entrada] = item++;              // Produz um item.
        entrada = (entrada + 1) % BUFFER_SIZE; // Atualiza a posição de entrada.

        printf("Produzido item %d\n", item);

        sem_post(&mutex); // Incrementa o semáforo mutex
        sem_post(&items); // Incrementa o semáforo items

        sleep(1); // Simula um tempo de produção
    }
    return NULL; // Nunca chega aqui
}

void *consumer(void *arg)
{
    while (1)
    {
        sem_wait(&items); // Decrementa o semáforo items
        sem_wait(&mutex); // Decrementa o semáforo mutex

        int item = buffer[saida];          // Consome um item
        saida = (saida + 1) % BUFFER_SIZE; // Atualiza a posição de saída

        printf("Consumido item %d\n", item);

        sem_post(&mutex);  // Incrementa o semáforo mutex
        sem_post(&spaces); // Incrementa o semáforo spaces

        sleep(2); // Simula um tempo de consumo
    }
    return NULL; // Nunca chega aqui
}

int main()
{
    pthread_t thread_producer, thread_consumer;

    // Inicializa os semáforos
    sem_init(&mutex, 0, 1);            // Mutex // Inicializa o semáforo mutex com o valor 1
    sem_init(&items, 0, 0);            // Items // Inicializa o semáforo items com o valor 0
    sem_init(&spaces, 0, BUFFER_SIZE); // Spaces // Inicializa o semáforo spaces com o valor BUFFER_SIZE

    pthread_create(&thread_producer, NULL, producer, NULL); // Cria a thread produtora
    pthread_create(&thread_consumer, NULL, consumer, NULL); // Cria a thread consumidora

    pthread_join(thread_producer, NULL); // Espera a thread produtora terminar
    pthread_join(thread_consumer, NULL); // Espera a thread consumidora terminar

    // Destrói os semáforos
    sem_destroy(&mutex);
    sem_destroy(&items);
    sem_destroy(&spaces);

    return 0;
}