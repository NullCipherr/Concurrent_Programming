// Problema dos filósofos jantando
//
// Neste problema, cinco filósofos estão sentados em uma mesa redonda com um prato de espaguete e um garfo entre cada par de filósofos. Cada filósofo precisa de dois garfos para comer.
// Como os garfos são compartilhados, um filósofo só pode comer se conseguir pegar os dois garfos adjacentes a ele.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

#define N 5               // Número de filósofos
pthread_mutex_t forks[N]; // Mutex para cada garfo

// O filosofo(nome do filosofo, ex: Maquiavel) pega os garfos
void *philosopher(void *arg)
{
    char *name = (char *)arg;
    int id = atoi(name);      // Converte o nome para um inteiro, EX: Maquiavel -> 0
    int left = id;            // Garfo à esquerda, mesmo índice, devido à circularidade
    int right = (id + 1) % N; // Garfo à direita, índice seguinte, devido à circularidade

    while (1)
    {
        printf("%s pensando\n", name);
        sleep(1); // Filósofo pensa por um tempo

        pthread_mutex_lock(&forks[left]);  // Pega o garfo à esquerda
        pthread_mutex_lock(&forks[right]); // Pega o garfo à direita

        printf("%s comendo\n", name);
        sleep(1); // Filósofo come por um tempo

        pthread_mutex_unlock(&forks[left]);  // Libera o garfo à esquerda
        pthread_mutex_unlock(&forks[right]); // Libera o garfo à direita

        printf("%s terminou de comer\n", name);
    }
    return NULL; // Nunca chega aqui
}

int main()
{
    pthread_t philosophers[N]; // Threads para os filósofos
    char names[N][20] = {"Maquiavel", "Aristóteles", "Descartes", "Kant", "Nietzsche"};

    for (int i = 0; i < N; i++)
    {
        pthread_mutex_init(&forks[i], NULL);                           // Inicializa os mutexes dos garfos
        pthread_create(&philosophers[i], NULL, philosopher, names[i]); // Cria a thread para o filósofo
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(philosophers[i], NULL); // Espera a thread terminar
    }

    for (int i = 0; i < N; i++)
    {
        pthread_mutex_destroy(&forks[i]); // Destrói os mutexes dos garfos
    }

    return 0;
}