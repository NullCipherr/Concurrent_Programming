/*
 * Compilar utilizando OpenMPI
 * mpicc arquivo -o arquivoMPI
 *
 * Este comando é utilizado para compilar um programa escrito em C que utiliza a biblioteca MPI (Message Passing Interface).
 * O comando 'mpicc' é o compilador específico para programas MPI. O parâmetro 'arquivo' é o nome do arquivo fonte que você deseja compilar,
 * e '-o arquivoMPI' especifica o nome do arquivo executável que será gerado após a compilação.
 *
 * Executar utilizando OpenMPI
 * mpirun -np <n_processos> executavel <args>
 *
 * Este comando é utilizado para executar um programa MPI. O comando 'mpirun' é o lançador de programas MPI.
 * O parâmetro '-np <n_processos>' especifica o número de processos que serão utilizados para executar o programa.
 * O parâmetro 'executavel' é o nome do arquivo executável que você deseja executar,
 * e '<args>' são os argumentos que você deseja passar para o programa.
 *
 * Execução em diversos hosts
 *
 * mpirun -host <ip_host>, ... ,<ip_hostn> executavel <args>
 *
 * Este comando é utilizado para executar um programa MPI em vários hosts (máquinas).
 * O parâmetro '-host <ip_host>, ... ,<ip_hostn>' especifica os endereços IP dos hosts onde o programa será executado.
 * O parâmetro 'executavel' é o nome do arquivo executável que você deseja executar,
 * e '<args>' são os argumentos que você deseja passar para o programa.
 *
 * Configurar em hostfile (Ver depois)
 *
 * -oversubscribe: Permite disparar um número maior de processos do que o número de núcleos do processador.
 *
 * Este parâmetro permite que você execute mais processos do que o número de núcleos disponíveis no processador.
 * Isso pode ser útil em situações onde você deseja maximizar o uso dos recursos disponíveis,
 * mesmo que isso possa levar a uma sobrecarga do sistema.
 *
 * Rotinas Básicas:
 * Estas são algumas das rotinas básicas da biblioteca MPI:
 *
 * - MPI_Init: Inicializa o ambiente MPI. Deve ser chamada no início do programa.
 * - MPI_Comm_size: Retorna o número total de processos no comunicador.
 * - MPI_Comm_rank: Retorna o identificador (rank) do processo chamador no comunicador.
 * - MPI_Send: Envia uma mensagem para outro processo.
 * - MPI_Recv: Recebe uma mensagem de outro processo.
 * - MPI_Finalize: Finaliza o ambiente MPI. Deve ser chamada no final do programa.
 *
 */

#include <mpi.h>

int main()
{
	return 0 ;
}
