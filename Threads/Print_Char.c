#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Desafio: Print Char
// Objetivo: Crie três threads para imprimir caracteres específicos em sequência.
// exemplo: thread 1 imprime o caractere 'a', thread 2 imprime o caractere 'b', thread 3 imprime o caractere 'c'.
// saída esperada: a, b, c.

#define NUM_THREADS 3

void *printChar(void *arg)
{
    char c = *(char *)arg;
    printf("%c\n", c);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    char chars[3] = {'a', 'b', 'c'};

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, printChar, (void *)&chars[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}