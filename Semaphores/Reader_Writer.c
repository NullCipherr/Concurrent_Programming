// Problema do Leitor-Escritor
//
// Neste problema, multiplos leitores podem ler simulataneamente um recurso compartilhado, mas apenas um escritor pode escrever no recurso por vez.
// Caso um escritor esteja escrevendo, nenhum leitor pode ler.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex;      // Semáforo para controlar o acesso ao contador de leitores
sem_t write_lock; // Semáforo para controlar o acesso ao escritor
int readers = 0;  // Contador de leitores

void *reader(void *arg)
{
    int id = *(int *)arg;
    free(arg); // Libera a memória alocada para o id

    while (1)
    {
        sem_wait(&mutex); // Entra na região crítica
        readers++;        // Incrementa o contador de leitores
        if (readers == 1)
        {
            sem_wait(&write_lock); // Se for o primeiro leitor, bloqueia o escritor
        }
        sem_post(&mutex); // Sai da região crítica

        // Lê o recurso compartilhado
        printf("Leitor %d está lendo\n", id);
        sleep(1);

        sem_wait(&mutex); // Entra na região crítica
        readers--;        // Decrementa o contador de leitores
        if (readers == 0)
        {
            sem_post(&write_lock); // Se for o último leitor, libera o escritor
        }
        sem_post(&mutex); // Sai da região crítica

        // Simula um tempo de espera antes de ler novamente
        sleep(1);
    }
}

void *writer(void *arg)
{
    int id = *(int *)arg;
    free(arg); // Libera a memória alocada para o id

    while (1)
    {
        sem_wait(&write_lock); // Bloqueia o escritor

        // Escreve no recurso compartilhado
        printf("Escritor %d está escrevendo\n", id);
        sleep(2);

        sem_post(&write_lock); // Libera o escritor

        // Simula um tempo de espera antes de escrever novamente
        sleep(2);
    }
}

int main()
{
    printf("Digite o número de leitores: ");
    int n_leitores;
    scanf("%d", &n_leitores);

    printf("Digite o número de escritores: ");
    int n_escritores;
    scanf("%d", &n_escritores);

    pthread_t leitores[n_leitores];     // Threads para os leitores
    pthread_t escritores[n_escritores]; // Threads para os escritores

    sem_init(&mutex, 0, 1);      // Inicializa o semáforo mutex com 1
    sem_init(&write_lock, 0, 1); // Inicializa o semáforo write_lock com 1

    for (int i = 0; i < n_leitores; i++)
    {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&leitores[i], NULL, reader, id); // Cria a thread para o leitor
    }

    for (int i = 0; i < n_escritores; i++)
    {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&escritores[i], NULL, writer, id); // Cria a thread para o escritor
    }

    // Espera as threads terminarem (neste caso, elas nunca terminam, então o programa ficará em execução indefinidamente)
    for (int i = 0; i < n_leitores; i++)
    {
        pthread_join(leitores[i], NULL);
    }

    for (int i = 0; i < n_escritores; i++)
    {
        pthread_join(escritores[i], NULL);
    }

    sem_destroy(&mutex);      // Destrói o semáforo mutex
    sem_destroy(&write_lock); // Destrói o semáforo write_lock

    return 0;
}