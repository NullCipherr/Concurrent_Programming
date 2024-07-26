#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Desafio: Contagem de Vogais
// Objetivo: Crie uma thread para contar e imprimir a quantidade de vogais em uma palavra.
// exemplo: thread 1 conta e imprime a quantidade de vogais na palavra "arara".
// saída esperada: 3.

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

    printf("%d\n", vowels);
}

int main()
{
    pthread_t thread;
    char *word = "arara";

    pthread_create(&thread, NULL, countVowels, (void *)word);
    pthread_join(thread, NULL);

    return 0;
}