/* 
   Desafio 2: somar os elementos de um vetor de inteiros da seguinte forma: 
              o processo 0 envia partes do vetor original para os demais 
              processos, cada processo calcula a soma da sua parte e 
              envia o resultado para o processo 0, que calcula a soma total
              e mostra na tela   
*/

#include <stdio.h>
#include <mpi.h>

#define SIZE_VECTOR 10
int vetor[SIZE_VECTOR] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

int main(int argc, char *argv[]) 
{
    int id, np, i, valor_env, tag = 1;
    int valor_rec;
    int elements_por_processo;
    int inicio_indice, final_indice;
    int soma_local = 0;
    int soma_total = 0;

    MPI_Status st;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    elements_por_processo = SIZE_VECTOR / np;

    if (id == 0) 
    {
        // Processo 0 envia partes do vetor para os demais processos
        for (i = 1; i < np; i++) 
        {
            inicio_indice = i * elements_por_processo;
            final_indice = (i == np - 1) ? SIZE_VECTOR : inicio_indice + elements_por_processo;
            for (int j = inicio_indice; j < final_indice; j++) 
            {
                MPI_Send(&vetor[j], 1, MPI_INT, i, tag, MPI_COMM_WORLD);
                printf("Processo %d enviou %d para processo %d\n", id, vetor[j], i);
            }
        }

        // Processo 0 calcula a soma da sua parte do vetor
        inicio_indice = 0;
        final_indice = elements_por_processo;
        for (i = inicio_indice; i < final_indice; i++) 
        {
            soma_local += vetor[i];
        }

        // Processo 0 recebe as somas dos demais processos
        for (i = 1; i < np; i++) 
        {
            MPI_Recv(&valor_rec, 1, MPI_INT, i, tag, MPI_COMM_WORLD, &st);
            printf("Processo %d recebeu soma parcial %d do processo %d\n", id, valor_rec, i);
            soma_total += valor_rec;
        }

        // Processo 0 soma sua parte com as somas recebidas
        soma_total += soma_local;
        printf("Soma total do vetor: %d\n", soma_total);
    } 
    else 
    {
        // Demais processos recebem suas partes do vetor e calculam a soma
        soma_local = 0;
        inicio_indice = id * elements_por_processo;
        final_indice = (id == np - 1) ? SIZE_VECTOR : inicio_indice + elements_por_processo;
        for (i = inicio_indice; i < final_indice; i++) 
        {
            MPI_Recv(&valor_rec, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &st);
            printf("Processo %d recebeu %d do processo %d\n", id, valor_rec, 0);
            soma_local += valor_rec;
        }

        // Os demais processos enviam suas somas para o processo 0
        MPI_Send(&soma_local, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
        printf("Processo %d enviou soma parcial %d para processo %d\n", id, soma_local, 0);
    }

    MPI_Finalize();
    return 0;
}
