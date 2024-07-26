#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Desafio: Multiplicação de Números
// Objetivo : Crie três threads, onde cada uma calcula o produto de dois números diferentes e imprima o resultado.
// Exemplo: 2 * 3, 4 * 5, 6 * 7
// Saída esperada: 6, 20, 42.

#define NUM_THREADS 3

void *multiplication(void *arg)
{
    int *numbers = (int *)arg;
    int num1 = numbers[0];
    int num2 = numbers[1];

    printf("%d * %d = %d\n", num1, num2, num1 * num2);
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int numbers[3][2] = {{2, 3}, {4, 5}, {6, 7}};

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, multiplication, (void *)&numbers[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}