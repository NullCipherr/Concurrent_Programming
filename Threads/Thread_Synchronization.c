#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Sincronização de threads
// Um dos principais problemas de programação concorrente é a sincronização de threads.
// A sincronização de threads é necessária para garantir que:
// - Threads cooperem entre si
// - Evitar condições de corrida
// - Garantir a consistência dos dados
// - Evitar deadlocks

// Conceitos de sincronização
// - Condição de corrida : Ocorre quando duas ou mais threads tentam acessar um recurso compartilhado ao mesmo tempo
// - Mutex (Mutual Exclusion) : Garante que apenas uma thread execute um bloco de código por vez
// - Variável de condição : Permite que uma thread aguarde até que uma condição seja satisfeita
// - Barreira : Permite que um grupo de threads aguarde até que todas as threads tenham alcançado um determinado ponto.

#define NUM_THREADS 5

int contador = 0; // Recurso compartilhado
pthread_mutex_t mutex;

void *minhaThread(void *arg)
{
    int id = *(int *)arg;

    pthread_mutex_lock(&mutex); // Bloqueia o mutex
    contador++;                 // Modifica o recurso compartilhado
    printf("Thread %d incrementou contador para %d\n", id, contador);
    pthread_mutex_unlock(&mutex); // Desbloqueia o mutex

    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];

    // Inicializa o mutex
    pthread_mutex_init(&mutex, NULL);

    // Cria threads
    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_args[i] = i + 1;
        int ret = pthread_create(&threads[i], NULL, minhaThread, (void *)&thread_args[i]);
        if (ret != 0)
        {
            printf("Erro ao criar a thread %d\n", i + 1);
            exit(EXIT_FAILURE);
        }
    }

    // Espera as threads terminarem
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Destrói o mutex
    pthread_mutex_destroy(&mutex);

    printf("Valor final do contador: %d\n", contador);
    return 0;
}