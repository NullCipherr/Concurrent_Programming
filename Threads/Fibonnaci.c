#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Desafio: Sequência de Fibonacci
// Objetivo :  Crie três threads para calcular os três primeiros números da sequência de Fibonacci e imprima-os.
// exemplo: thread 1 calcula o primeiro número da sequência de Fibonacci, thread 2 calcula o segundo número da sequência de Fibonacci, thread 3 calcula o terceiro número da sequência de Fibonacci.
// saída esperada: 0, 1, 1.

// Fibonnaci é uma sequência de números inteiros, começando normalmente por 0 e 1, na qual, cada termo subsequente corresponde à soma dos dois anteriores.
// 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, ...
// exemplo: 0 + 1 = 1, 1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8, ...
// fibonacci(0) = 0
// fibonacci(1) = 1
// fibonacci(n) = fibonacci(n - 1) + fibonacci(n - 2)

#define NUM_THREADS 3

int fibonacci(int n)
{
    if (n <= 1)
    {
        return n;
    }
    else
    {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

void *calculateFibonacci(void *arg)
{
    int n = *(int *)arg;
    int result = fibonacci(n);
    printf("O resultado é -> %d\n", result);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int numbers[3] = {0, 1, 2};

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, calculateFibonacci, (void *)&numbers[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}