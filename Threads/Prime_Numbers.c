#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

// Desafio: Números Primos
// Objetivo : Crie três threads, onde cada uma verifica se um número é primo e imprime os números primos encontrados.
// exemplo: thread 1 verifica se 7 é primo, thread 2 verifica se 11 é primo, thread 3 verifica se 13 é primo.
// saída esperada: 7 é primo, 11 é primo, 13 é primo.

// Um numero primo é um número natural maior que 1, que só é divisível por 1 e por ele mesmo.
// exemplo: 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, ...

int NUM_THREADS = 3;

void *checkPrimeNumber(void *arg)
{
    int number = *(int *)arg;
    bool isPrime = true;

    if (number <= 1)
    {
        isPrime = false;
    }
    else
    {
        for (int i = 2; i <= number / 2; i++)
        {
            if (number % i == 0)
            {
                isPrime = false;
                break;
            }
        }
    }

    if (isPrime)
    {
        printf("%d é primo\n", number);
    }
    else
    {
        printf("%d não é primo\n", number);
    }
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int numbers[3] = {7, 11, 8};

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, checkPrimeNumber, (void *)&numbers[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}