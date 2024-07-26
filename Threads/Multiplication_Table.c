#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Desafio : Tabuada
// Objetivo : Crie uma thread para calcular e imprimir a tabuada de um número escolhido.
// exemplo: thread 1 calcula e imprime a tabuada do número 2.
// saída esperada: 2, 4, 6, 8, 10, 12, 14, 16, 18, 20.

void *calculateMultiplicationTable(void *arg)
{
    int n = *(int *)arg;

    for (int i = 1; i <= 10; i++)
    {
        printf("%d\n", n * i);
    }
}

int main()
{
    pthread_t thread;
    int number = 4;

    pthread_create(&thread, NULL, calculateMultiplicationTable, (void *)&number);
    pthread_join(thread, NULL);

    return 0;
}