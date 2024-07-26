// Aluno e RA
// Andrei Roberto da Costa 107975
// João Gilberto Pelisson Casagrandre 112684

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *funcaoCalculaFatorial(void *ptr);

int nthreads;
int n;

struct tipoPack
{
    char mensagem[16];
    int start;
    int end;
    double fat;
};

typedef struct tipoPack tipoPack;

void main(void)
{
    pthread_t thread[50];

    int i, iret[50];
    char str_nt[3];

    tipoPack pack[50];

    printf("\nEntre com o numero de threads => ");
    scanf("%d", &nthreads);

    printf("\nEntre com o numero para calcular o fatorial => ");
    scanf("%d", &n);

    int chunk = n / nthreads;
    int remainder = n % nthreads;

    int current_start = 1;

    for (i = 0; i < nthreads; i++)
    {
        sprintf(str_nt, "%d", i);
        strcpy(pack[i].mensagem, "\nSou a thread ");
        strcat(pack[i].mensagem, str_nt);
        pack[i].fat = 1.0;

        pack[i].start = current_start;
        if (i < remainder)
        {
            pack[i].end = current_start + chunk;
        }
        else
        {
            pack[i].end = current_start + chunk - 1;
        }
        current_start = pack[i].end + 1;
    }

    for (i = 0; i < nthreads; i++)
        iret[i] = pthread_create(&(thread[i]), NULL, funcaoCalculaFatorial, (void *)&pack[i]);

    for (i = 0; i < nthreads; i++)
        pthread_join(thread[i], NULL);

    double total_fatorial = 1.0;
    for (i = 0; i < nthreads; i++)
    {
        printf("\n%s: Calcularei a parcial fatorial de %d ate %d: %lf\n", pack[i].mensagem, pack[i].start, pack[i].end, pack[i].fat);
        total_fatorial *= pack[i].fat;
    }

    printf("\n O Fatorial de %d eh: %lf\n", n, total_fatorial);

    exit(0);
}

void *funcaoCalculaFatorial(void *ptr)
{
    tipoPack *pack;

    pack = (tipoPack *)ptr;

    printf("%s: Calculando o fatorial de %d ate %d\n", pack->mensagem, pack->start, pack->end);

    for (int i = pack->start; i <= pack->end; i++)
    {
        pack->fat *= i;
    }
}