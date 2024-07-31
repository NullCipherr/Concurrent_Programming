#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Desafio: Fatorial de Números
// Objetivo : Crie três threads, onde cada uma calcula o fatorial de um número diferente (por exemplo, 4, 5, e 3) e imprima o resultado.
// Exemplo: 4!, 5!, 3!.
// Saída esperada: O Fatorial de 4 é 24, O Fatorial de 5 é 120, O Fatorial de 3 é 6.

// O Fatorial de um número n é o produto de todos os inteiros positivos menores ou iguais a n.
// Exemplo: 4! = 4 * 3 * 2 * 1 = 24.
// Exemplo: 5! = 5 * 4 * 3 * 2 * 1 = 120.
// Exemplo: 3! = 3 * 2 * 1 = 6.

#define NUM_THREADS 3

void *factorial(void *arg)
{
    int num = *(int *)arg;
    int fact = 1;

    for (int i = 1; i <= num; i++)
    {
        fact *= i;
    }

    printf("O Fatorial de %d é %d\n", num, fact);
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int numbers[3] = {4, 5, 3};

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, factorial, (void *)&numbers[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}