/*

Exemplo 03: Faca um programa que declare e inicialize um vetor de 1000 elementos.
Cada processo devera calcular a media aritmetica de uma parte diferente do vetor.
Cada processo devera imprimir na tela a sua identificacao (id ou rank), o seu
intervalo dos dados, a sua parte do vetor e a media final.

Salve este arquivo com o nome exemplo03.c

Compile-o em um terminal pela linha de comando, da seguinte forma:

>mpicc exemplo03.c -o exemplo03 <enter>

Depois execute-o pela linha de comando, da seguinte forma:

>mpirun -np 6 ./exemplo03 <enter>

Atenção: talvez seja necessario utilizar a opção --oversubscribe na
linha de comando do mpirun para permitir executar mais processos doque
o numero de cores/processadores.

Analise o codigo e a execucao. Teste diferentes numeros de processos.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char *argv[]){
    int id, np, i, tamVet=1000, faixa, resto, inicio, fim;
    double soma=0.0, media=0.0;

    int vetor[1000];

    srand(time(NULL));

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&np);

    printf("\nID do Processo: %d, Total de Processos: %d\n", id, np);

    for (i=0;i<tamVet;i++)
        vetor[i]=rand()%100;

    faixa=tamVet/np;
    resto=tamVet%np;

    inicio=id*faixa;

    if (resto>id)
    {
        inicio=inicio+id;
        fim=inicio+faixa;
    }
    else
    {   inicio=inicio+resto;
        fim=inicio+faixa-1;
    }

    printf("\nProcesso %d trabalha no intervalo %d ate %d\n", id, inicio, fim);
    for (i=inicio; i<=fim; i++)
    {
        soma=soma+vetor[i];
    }
    media=soma/(double)(fim-inicio+1);
    printf("Processo %d, Soma = %.2lf, Nro Elem = %d, Media = %.2lf\n", id, soma, (fim-inicio+1), media);

    while (1) {};

    MPI_Finalize();
}

