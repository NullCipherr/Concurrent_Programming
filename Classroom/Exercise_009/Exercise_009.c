// Aluno e RA
// Andrei Roberto da Costa 107975

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define maxVet 10000
#define maxNumero 10000

typedef int tipoVetor[maxVet];

tipoVetor A;
int tamA;

typedef struct
{
    tipoVetor *V;
    int ini;
    int fim;
} thread_data_t;

int leTam(void)
{
    int tam;
    do
    {
        printf("\nDigite o tamanho do Vetor = ");
        scanf("%d", &tam);
    } while ((tam < 1) || (tam > maxVet));
    return tam;
}

void geraVetor(tipoVetor V, int tam)
{
    int i, sinal;
    srand(time(NULL));
    printf("\nGeracao Aleatoria do Vetor\n");
    for (i = 0; i < tam; i++)
    {
        V[i] = rand() % maxNumero;
        sinal = (rand() % 2) * 2 - 1; // se rand%2==0, sinal=-1; se rand%2==1, sinal=+1
        V[i] = sinal * V[i];          // impõe o sinal no número
    }
}

void mostraVetor(char *id, tipoVetor V, int tam)
{
    int i;
    printf("\nElementos do Vetor %s:\n", id);
    printf("%d", V[0]);
    for (i = 1; i < tam; i++)
    {
        printf(", %d", V[i]);
    }
    printf("\n");
}

void mergeMetades(tipoVetor V, int ini, int meio, int fim)
{
    tipoVetor auxV1, auxV2;
    int tam1 = 0, tam2 = 0, maior, i, i1, i2;

    for (i = ini; i <= meio; i++)
    {
        auxV1[tam1] = V[i];
        tam1++;
    }

    for (i = meio + 1; i <= fim; i++)
    {
        auxV2[tam2] = V[i];
        tam2++;
    }

    if (auxV1[tam1 - 1] > auxV2[tam2 - 1])
        maior = abs(auxV1[tam1 - 1]) + 1;
    else
        maior = abs(auxV2[tam2 - 1]) + 1;

    auxV1[tam1] = maior;
    auxV2[tam2] = maior;

    i1 = 0;
    i2 = 0;
    for (i = ini; i <= fim; i++)
    {
        if (auxV1[i1] < auxV2[i2])
        {
            V[i] = auxV1[i1];
            i1++;
        }
        else
        {
            V[i] = auxV2[i2];
            i2++;
        }
    }
}

void *mergeSort(void *arg)
{
    thread_data_t *data = (thread_data_t *)arg;
    tipoVetor *V = data->V;
    int ini = data->ini;
    int fim = data->fim;

    if (fim > ini)
    {
        int meio = (ini + fim) / 2;

        pthread_t thread1, thread2;
        thread_data_t data1 = {V, ini, meio};
        thread_data_t data2 = {V, meio + 1, fim};

        pthread_create(&thread1, NULL, mergeSort, &data1);
        pthread_create(&thread2, NULL, mergeSort, &data2);

        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);

        mergeMetades(*V, ini, meio, fim);
    }

    return NULL;
}

int main(void)
{
    int resp;

    do
    {
        tamA = leTam();
        geraVetor(A, tamA);
        mostraVetor("A Original", A, tamA);

        printf("\nOrdenando A por Merge Sort ...\n");

        thread_data_t data = {&A, 0, tamA - 1};
        mergeSort(&data);

        mostraVetor("A Ordenado", A, tamA);

        printf("\nDeseja Nova Execucao, <1>Sim <2>Nao? => ");
        scanf("%d", &resp);
    } while (resp == 1);

    return 0;
}
