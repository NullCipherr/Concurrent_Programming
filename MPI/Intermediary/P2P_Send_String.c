// Desafio 1: substituir o envio de um inteiro por uma string.

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
    	char string1[] = "Hello";
    	MPI_Send(&string1,10,MPI_CHAR,1,tag, MPI_COMM_WORLD);
    	MPI_Recv(&valor_rec,10,MPI_CHAR,1,tag, MPI_COMM_WORLD,&st);
    	printf("id %d enviou %s e recebeu %s\n",id,string1, valor_rec);
  	}
 	else if (id==1)
    {
        char string2[] = "World!";
        MPI_Send(&string2,10,MPI_CHAR,0,tag, MPI_COMM_WORLD);
        MPI_Recv(&valor_rec, 10,MPI_CHAR,0,tag, MPI_COMM_WORLD,&st);
        printf("id %d enviou %s e recebeu %s\n",id, string2, valor_rec);
    }
    else 
    {
        printf("id %d nao enviou e nem recebeu mensagem\n",id);
	}

  	MPI_Finalize();

  	return 0;
}      
