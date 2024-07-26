#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Biblioteca pthread.h
// - Permite a criação de threads em programas C
// - Sincronização de threads
// - Comunicação entre threads
//
// Tipo de dado
// - pthread_t : Tipo de dado que representa uma thread
//
// Funções
// - pthread_create() : Cria uma nova thread
// - pthread_exit() : Termina a execução de uma thread
// - pthread_join() : Espera a finalização de uma thread
// - pthread_cancel() : Cancela a execução de uma thread

// Thread é uma sequência de instruções que podem ser executadas concorrentemente
// - Identificador único
// - Pilha
// - Registradores

// Esta função é executada por cada thread criada. Ela recebe um argumento genérico void*
// que é convertido para um ponteiro para int para obter o ID da thread.
// OBS: Ponteiro genérico - void* - pode apontar para qualquer tipo de dado.
void *minhaThread(void *arg)
{
    int id = *(int *)arg;
    printf("Thread %d\n", id);
    pthread_exit(NULL);
}

int main()
{
    int n;

    printf("Digite o numero de threads: ");
    scanf("%d", &n);
    pthread_t threads[n];
    int thread_args[n];

    for (int i = 0; i < n; i++)
    {
        thread_args[i] = i;
        int ret = pthread_create(&threads[i], NULL, minhaThread, &thread_args[i]);

        // Verificação de erro
        if (ret != 0)
        {
            printf("Erro na criação da thread %d\n", i);
            exit(1);
        }
    }

    // Espera as threads finalizarem
    for (int i = 0; i < n; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Todas as threads finalizaram\n");

    return 0;
}