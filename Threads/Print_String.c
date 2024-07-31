#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Desafio: Impressão de Strings
// Objetivo : Crie três threads, onde cada uma imprime uma string diferente.
// Exemplo: "Hello", "World", "Threads"
// Saída esperada: Hello, World, Threads.

#define NUM_THREADS 3

void *printString(void *arg)
{
    char *string = (char *)arg;
    printf("%s\n", string);
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    char *strings[3] = {"Hello", "World", "Threads"};

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, printString, (void *)strings[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}