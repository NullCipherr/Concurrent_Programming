#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Desafio: Impressão de Números Pares e Ímpares
// Objetivo : Crie duas threads, uma que imprime números pares de 1 a 10 e outra que imprime números ímpares de 1 a 10.
// exemplo: thread 1 imprime 2, 4, 6, 8, 10, thread 2 imprime 1, 3, 5, 7, 9.
// Saída esperada: Par: 2, Par: 4, Par: 6, Par: 8, Par: 10, Impar: 1, Impar: 3, Impar: 5, Impar: 7, Impar: 9.

void *imprimePar(void *arg)
{
    // Inbtervalo de 1 a 10
    for (int i = 2; i <= 10; i += 2)
    {
        printf("Par: %d\n", i);
    }
    pthread_exit(NULL);
}

void *imprimeImpar()
{
    for (int i = 1; i <= 10; i += 2)
    {
        printf("Impar : %d\n", i);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t thread_par, thread_impar;

    pthread_create(&thread_par, NULL, imprimePar, NULL);
    pthread_create(&thread_impar, NULL, imprimeImpar, NULL);

    pthread_join(thread_par, NULL);
    pthread_join(thread_impar, NULL);

    return 0;
}