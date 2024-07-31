/*

Exemplo 02: Testes com a identificacao de processos no OPENMPI.

Salve este arquivo com o nome exemplo02.c

Compile-o em um terminal pela linha de comando, da seguinte forma:

>mpicc exemplo02.c -o exemplo02 <enter>

Depois execute-o pela linha de comando, da seguinte forma:

>mpirun -np 5 ./exemplo02 bla ble bli blo blu <enter>

Atencao: talvez seja necessario utilizar a opcao --oversubscribe na
linha de comando do mpirun para permitir executar mais processos doque
o numero de cores/processadores.

Analise o codigo e a execucao. Teste diferentes numeros de processos.

*/

#define SIZE_VECTOR 1000 
int vetor[SIZE_VECTOR] ;

int sum_media_aritmetica ;

#include <stdio.h>
#include <mpi.h>

void initialize_vector()
{
    for(int i = 0 ; i < SIZE_VECTOR ; i++)
    {
        vetor[i] = i + 1 ;
    }
}

void mostra_vetor()
{
    for(int i = 0 ; i < SIZE_VECTOR ; i++)
    {
        printf("V[%d]: %d\n" , i, vetor[i]);
    }
}

int main(int argc, char *argv[])
{
    int id, np, i;
    int elements_por_processo = SIZE_VECTOR / np;
    int inicio_indice, final_indice;
    int soma_local = 0 ;
    double media_aritmetica = 0.0 ;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&np);
    
    initialize_vector() ;
    
    printf("Número de processos: %d\n", np) ;
    printf("Limitando os processos ao vetor, fica %d\n", SIZE_VECTOR / np) ;
    printf("\nProcesso %d Quantidade = %d Argc = %d\n", id, np, argc);

    /*
        0 1 2 3 .. 500
        500 501 502 .. 999
    */
    
    inicio_indice = id * elements_por_processo;
    final_indice = (id == np - 1) ? SIZE_VECTOR : inicio_indice + elements_por_processo;

    for(i = inicio_indice ; i < final_indice; i++)
    {
        soma_local += vetor[i] ; 
    }
    
    media_aritmetica = soma_local / (final_indice - inicio_indice) ;
    
    
    printf("Processo %d: Intervalo [%d, %d], Média = %.2f\n", id, inicio_indice, final_indice - 1, media_aritmetica);
    
    while (1) {};
    // mostra_vetor() ;


    MPI_Finalize();
}

/* Desafio: Faca um programa que declare e inicialize estaticamente um
vetor de 1000 elementos e divida esse vetor equilibradamente entre os
processos, de forma que cada processo ira calcular a media aritmetica
de sua parte. Cada processo deve imprimir na tela a sua identificacao
(id ou rank), o seu intervalo dos dados, a sua parte do vetor e a media
final */
