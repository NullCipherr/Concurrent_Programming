/*

Exemplo 04: Testes com envio de mensagem (numero inteiro)
entre processos no OPENMPI.

Salve este arquivo com o nome exemplo04.c

Compile-o em um terminal pela linha de comando, da seguinte forma:

>mpicc exemplo04.c -o exemplo04 <enter>

Depois execute-o pela linha de comando, da seguinte forma:

>mpirun -np 5 ./exemplo04 <enter>

Atenção: talvez seja necessario utilizar a opção --oversubscribe na
linha de comando do mpirun para permitir executar mais processos doque 
o numero de cores/processadores.

Analise o codigo e a execucao. Teste diferentes numeros de processos.

*/

#define SIZE 10
int vetor[SIZE] ;

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{ 
	int id, np,i, valor_env,tag=1 ;
	char valor_rec[10];

  	MPI_Status st;
  	MPI_Init(&argc,&argv);
 	MPI_Comm_rank(MPI_COMM_WORLD,&id);
  	MPI_Comm_size(MPI_COMM_WORLD,&np);

  	if(id==0)
  	{
    		char string1[] = "Olá";
    		MPI_Send(&string1,10,MPI_CHAR,1,tag, MPI_COMM_WORLD);
    		MPI_Recv(&valor_rec,10,MPI_CHAR,1,tag, MPI_COMM_WORLD,&st);
    		printf("id %d enviou %s e recebeu %s\n",id,string1, valor_rec);
  	}
 	else if (id==1)
      	{
        	char string2[] = "Mundo";
        	MPI_Send(&string2,10,MPI_CHAR,0,tag, MPI_COMM_WORLD);
        	MPI_Recv(&valor_rec, 10,MPI_CHAR,0,tag, MPI_COMM_WORLD,&st);
        	printf("id %d enviou %s e recebeu %s\n",id, string2, valor_rec);
      	}
      	else {
        	printf("id %d nao enviou e nem recebeu mensagem\n",id);
	}

  	MPI_Finalize();

  	return 0;
}

/* Desafio 1: substituir o envio de um inteiro por uma string.

   Desafio 2: somar os elementos de um vetor de inteiros da seguinte forma: 
              o processo 0 envia partes do vetor original para os demais 
              processos, cada processo calcula a soma da sua parte e 
              envia o resultado para o processo 0, que calcula a soma total
              e mostra na tela
       
*/
