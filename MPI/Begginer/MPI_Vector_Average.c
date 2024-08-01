#include <stdio.h>
#include <mpi.h>

#define SIZE_VECTOR 1000
int vetor[SIZE_VECTOR];

void initialize_vector()
{
    for (int i = 0; i < SIZE_VECTOR; i++)
    {
        vetor[i] = i + 1;
    }
}

int main(int argc, char *argv[])
{
    int id, np, i;
    int elements_por_processo;
    int inicio_indice, final_indice;
    double soma_local = 0;
    double media_aritmetica = 0.0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    elements_por_processo = SIZE_VECTOR / np;

    initialize_vector();

    printf("\nProcesso %d Quantidade = %d Argc = %d\n", id, np, argc);

    /*
        0 1 2 3 .. 500
        500 501 502 .. 999
    */

    inicio_indice = id * elements_por_processo;
    final_indice = (id == np - 1) ? SIZE_VECTOR : inicio_indice + elements_por_processo;

    for (i = inicio_indice; i < final_indice; i++)
    {
        soma_local = soma_local + vetor[i];
    }

    media_aritmetica = (double)soma_local / (final_indice - inicio_indice);

    printf("Processo %d: Intervalo [%d, %d], Soma = %.2f, Média = %.2f\n", id, inicio_indice, final_indice - 1, soma_local, media_aritmetica);

    MPI_Finalize();
    return 0;
}

/* Desafio: Faca um programa que declare e inicialize estaticamente um
vetor de 1000 elementos e divida esse vetor equilibradamente entre os
processos, de forma que cada processo ira calcular a media aritmetica
de sua parte. Cada processo deve imprimir na tela a sua identificacao
(id ou rank), o seu intervalo dos dados, a sua parte do vetor e a media
final */
