/*

Exemplo 01: Testes iniciais com OPENMPI.

Salve este arquivo com o nome exemplo01.c

Compile-o em um terminal pela linha de comando, da seguinte forma:

>mpicc exemplo01.c -o exemplo01 <enter>

Depois execute-o pela linha de comando, da seguinte forma:

>mpirun -np 5 ./exemplo01 bla ble bli blo blu <enter>

Atenção: talvez seja necessario utilizar a opção --oversubscribe na
linha de comando do mpirun para permitir executar mais processos doque
o numero de cores/processadores.

Teste a execucao de outras formas, alterando o numero de processos e os
argumentos do executavel.

Analise o codigo e as execucoes.

Execute-o tambem em background, colocando um caracter '&' colado no
final da linha de comando, por exemplo:

>mpirun -np 5 ./exemplo01a bla ble bli blo blu& <enter> <enter>

Tecle duas vezes o <enter>. Observe que o prompt do terminal sera
liberado, mas os processos continuam em execucao.

Para ver os processos que estao em execucao, use o seguinte comando no
terminal:

>top <enter>

Para sair do comando top digite a letra 'q'.

Para matar os processos em execucao, use o seguinte comando no terminal:

>kill <numero do processo> <enter>

O numero do processo pode ser visualizado pelo comando top.

*/

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){
    int id, np,i;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&np);

    printf("\nProcesso %d Quantidade = %d Argc = %d\n", id, np, argc);

    printf("\n");
    for(i=0;i<argc-1;i++){
   	 printf("%s ",argv[i]);
    }
    printf("%s\n",argv[i]);

    while (1) {};

    MPI_Finalize();
}
