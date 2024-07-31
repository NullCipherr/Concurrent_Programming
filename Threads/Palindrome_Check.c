#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

// Desafio: Palindrome Check
// Objetivo: Crie três threads para verificar se uma palavra é um palíndromo.
// exemplo: thread 1 verifica se a palavra "arara" é um palíndromo, thread 2 verifica se a palavra "reviver" é um palíndromo, thread 3 verifica se a palavra "cachorro" é um palíndromo.
// saída esperada: arara é um palíndromo, reviver é um palíndromo, cachorro não é um palíndromo.

// Palindromo é uma palavra, frase ou número que se lê da mesma forma de trás para frente.
// exemplo: arara, reviver, 12321, 123321, 1234321, ...

#define NUM_THREADS 3

typedef struct
{
    char *word;
    int isPalindrome;
} Palindrome;

void *checkPalindrome(void *arg)
{
    Palindrome *palindrome = (Palindrome *)malloc(sizeof(Palindrome));
    palindrome->word = (char *)arg;
    palindrome->isPalindrome = 1;

    int length = strlen(palindrome->word);

    for (int i = 0; i < length / 2; i++)
    {
        if (palindrome->word[i] != palindrome->word[length - i - 1])
        {
            palindrome->isPalindrome = 0;
            break;
        }
    }
    if (palindrome->isPalindrome)
    {
        printf("%s é um palíndromo\n", palindrome->word);
    }
    else
    {
        printf("%s não é um palíndromo\n", palindrome->word);
    }
}

int main()
{
    pthread_t threads[NUM_THREADS];
    char *words[3] = {"arara", "reviver", "cachorro"};

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, checkPalindrome, (void *)words[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}