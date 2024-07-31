#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define NUM_THREADS 3

// Desafio: Ordenação de Strings
// Objetivo : Crie três threads para ordenar três strings diferentes e imprima as strings ordenadas.
// exemplo: thread 1 ordena a string "arara", thread 2 ordena a string "reviver", thread 3 ordena a string "cachorro".
// saída esperada: aaarr, eeirrv, acchorr.

void *sortString(void *arg)
{
    char *string = (char *)arg;
    int length = strlen(string);

    // Ordenação da string
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length - 1; j++)
        {
            if (string[j] > string[j + 1])
            {
                char temp = string[j];
                string[j] = string[j + 1];
                string[j + 1] = temp;
            }
        }
    }

    printf("String Ordenada -> %s\n", string);
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    char strings[3][10] = {"arara", "reviver", "cachorro"};

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, sortString, (void *)strings[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}