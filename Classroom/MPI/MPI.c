/*
 * 1. Compilar utilizando OpenMPI
 * 
 *      mpicc arquivo -o arquivoMPI
 *
 * Este comando é utilizado para compilar um programa escrito em C que utiliza a biblioteca MPI (Message Passing Interface).
 * O comando 'mpicc' é o compilador específico para programas MPI. 
 * O parâmetro 'arquivo' é o nome do arquivo fonte que você deseja compilar,
 * e '-o arquivoMPI' especifica o nome do arquivo executável que será gerado após a compilação.
 *
 * 2. Executar utilizando OpenMPI
 *
 *      mpirun -np <n_processos> executavel <args>
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
 * Configurar em hostfile
 *
 * Para configurar a execução em diversos hosts utilizando um arquivo de hostfile, siga os passos abaixo:
 *
 * 1. Crie um arquivo de texto chamado 'hostfile' com a lista de hosts onde o programa será executado.
 *    Cada linha do arquivo deve conter o endereço IP ou o nome do host. Por exemplo:
 *
 *    hostfile:
 *    192.168.1.1
 *    192.168.1.2
 *    192.168.1.3
 *
 * 2. Utilize o comando 'mpirun' com a opção '-hostfile' para especificar o arquivo de hostfile:
 *
 *    mpirun -hostfile hostfile -np <n_processos> executavel <args>
 *
 *    Este comando executará o programa MPI nos hosts especificados no arquivo 'hostfile',
 *    utilizando o número de processos especificado por '-np <n_processos>'.
 *
 * -oversubscribe: Permite disparar um número maior de processos do que o número de núcleos do processador.
 *
 * Este parâmetro permite que você execute mais processos do que o número de núcleos disponíveis no processador.
 * Isso pode ser útil em situações onde você deseja maximizar o uso dos recursos disponíveis,
 * mesmo que isso possa levar a uma sobrecarga do sistema.
 *
 * Rotinas Básicas:
 *
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
