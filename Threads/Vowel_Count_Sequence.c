#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

// Desafio: Contagem de Vogais em frase
// Objetivo: Crie uma thread para contar e imprimir a quantidade de vogais em uma frase.
// exemplo: thread 1 conta e imprime a quantidade de vogais na frase "arara é um animal".
// saída esperada: 8.

// Vogais são as letras a, e, i, o, u.

void *countVowels(void *arg)
{
    char *word = (char *)arg;
    int vowels = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        if (word[i] == 'a' || word[i] == 'e' || word[i] == 'i' || word[i] == 'o' || word[i] == 'u')
        {
            vowels++;
        }
    }

    printf("A frase possui %d vogais \n", vowels);
}

int main()
{
    pthread_t thread;
    char *word = "arara é um animal";

    pthread_create(&thread, NULL, countVowels, (void *)word);
    pthread_join(thread, NULL);

    return 0;
}