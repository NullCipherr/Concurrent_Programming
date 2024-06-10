// Aluno e RA
// Andrei Roberto da Costa RA107975

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *fatorial(void *ptr);

struct tipoFatData {
    char nome[10];
    int n, fat;
};

typedef struct tipoFatData tipoFatData;

int main(void)
{
    int numero_threads;

    printf("Digite o número de Threads: ");
    scanf("%d", &numero_threads);

    pthread_t threads[numero_threads];
    tipoFatData fatData[numero_threads];

    for (int i = 0; i < numero_threads; i++) {
        printf("Valor fatorial da Thread[%d] -> ", i + 1);
        scanf("%d", &fatData[i].n);
        strcpy(fatData[i].nome, "Thread");
        fatData[i].fat = 1;
    }

    for (int i = 0; i < numero_threads; i++) {
        pthread_create(&threads[i], NULL, fatorial, (void *)&fatData[i]);
    }

    for (int i = 0; i < numero_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < numero_threads; i++) {
        printf("\n%s [%d]: Fatorial -> %d\n", fatData[i].nome, i, fatData[i].fat);
    }

    return 0;
}

void *fatorial(void *ptr)
{
    int i;
    tipoFatData *fatData = (tipoFatData *)ptr;

    printf("\n%s: vou calcular uma fatorial", fatData->nome);

    for (i = fatData->n; i > 1; i--) {
        fatData->fat *= i;
    }

    return NULL;
}
