#include <mpi.h>
#include <stdio.h>

// Comunicação ponto a ponto entre dois processos
int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv); // Inicializa o MPI

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Pega o rank do processo
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Pega o número de processos

    // Se o rank for 0, envia uma mensagem para o processo 1
    if (rank == 0)
    {
        int message = 42;
        MPI_Send(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent message %d to process 1\n", message);
    }
    else if (rank == 1) // Se o rank for 1, recebe a mensagem do processo 0
    {
        int message;
        MPI_Recv(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received message %d from process 0\n", message);
    }

    MPI_Finalize();
    return 0;
}