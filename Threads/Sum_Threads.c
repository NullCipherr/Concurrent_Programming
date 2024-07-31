#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Desafio: Soma de Números
// Objetivo: Cada thread deve calcular e imprimir a soma dos números de 1 até o seu ID (por exemplo, a thread 3 deve calcular 1 + 2 + 3).
// Além disso, as threads devem retornar o resultado da soma, e o main deve imprimir o resultado de cada thread.
// Exemplo: thread 1 imprime 1, thread 2 imprime 3, thread 3 imprime 6.
// Saída esperada: Thread 1 (0) retornou 0, Thread 2 (1) retornou 1, Thread 3 (2) retornou 3.

void *minhaThread(void *arg)
{
    int id = *(int *)arg;
    int soma = 0;
    printf("Thread %d\n", id);

    // Calcula a soma dos números de 1 até id
    for (int i = 0; i < id; i++)
    {
        soma += i;
    }

    // Retorna a soma
    int *resultado = malloc(sizeof(int));
    *resultado = soma;
    pthread_exit((void *)resultado);
}

int main()
{
    int n;

    printf("Digite o numero de threads: ");
    scanf("%d", &n);

    pthread_t threads[n];
    int thread_args[n];
    int *resultado;

    for (int i = 0; i < n; i++)
    {
        thread_args[i] = i + 1;
        int ret = pthread_create(&threads[i], NULL, minhaThread, (void *)&thread_args[i]);

        // Verificação de erro
        if (ret != 0)
        {
            printf("Erro na criação da thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    // Espera as threads finalizarem
    for (int i = 0; i < n; i++)
    {
        pthread_join(threads[i], (void **)&resultado);
        printf("Thread %d (%d) retornou %d\n", i + 1, i, *resultado);
        free(resultado);
    }

    printf("Todas as threads finalizaram\n");
    return 0;
}