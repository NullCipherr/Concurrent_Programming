/*

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

int main(int argc, char *argv[])
{
    int id, np, i;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    printf("\nProcesso %d Quantidade = %d Argc = %d\n", id, np, argc);

    printf("\n");
    for (i = 0; i < argc - 1; i++)
    {
        printf("%s ", argv[i]);
    }
    printf("%s\n", argv[i]);

    while (1)
    {
    };

    MPI_Finalize();
}
