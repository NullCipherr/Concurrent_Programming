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

#include <stdio.h>
#include <mpi.h>

#define SIZE_VECTOR 10
int vetor[SIZE_VECTOR] = {1,2,3,4,5,6,7,8,9,10} ;

int main(int argc, char *argv[])
{ 
	int id, np,i, valor_env,tag=1 ;
	int valor_rec;
	int elements_por_processo;
	int inicio_indice, final_indice;
	int soma_local = 0.0 ;

  	MPI_Status st;
  	MPI_Init(&argc,&argv);
 	MPI_Comm_rank(MPI_COMM_WORLD,&id);
  	MPI_Comm_size(MPI_COMM_WORLD,&np);
	
	elements_por_processo = SIZE_VECTOR / np;
    
    // printf("Elementos por processo %d", elements_por_processo) ;
	
	    if(id==0)
  		{
  		    inicio_indice = id * elements_por_processo;
            final_indice = (id == np - 1) ? SIZE_VECTOR : inicio_indice + elements_por_processo;
  		    // ENVIA PARTES DO VETOR ORIGINAL PARA OS DEMAIS PROCESSOS
  		    for(int i = 0 ; i < elements_por_processo; i++)
            {
                int value = vetor[i+inicio_indice] ;
                MPI_Send(&value,1,MPI_INT,1,tag, MPI_COMM_WORLD);
    		    MPI_Recv(&valor_rec,1,MPI_INT,1,tag, MPI_COMM_WORLD,&st);
    		    printf("id %d enviou %d e recebeu %s\n",id,vetor, valor_rec);
            }
      	}
     	else if (id != 0)
        {
            inicio_indice = id * elements_por_processo;
            final_indice = (id == np - 1) ? SIZE_VECTOR : inicio_indice + elements_por_processo;
            
                MPI_Recv(&valor_rec, 1,MPI_INT,0,tag, MPI_COMM_WORLD,&st); // Recebe a sua parte do vetor
            soma_local = soma_local + valor_rec ;
            
            MPI_Send(&soma_local,1,MPI_INT,0,tag, MPI_COMM_WORLD); // Envia o resultado para o processo 0.
            printf("id %d enviou %s e recebeu %s\n",id, soma_local, valor_rec);
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
