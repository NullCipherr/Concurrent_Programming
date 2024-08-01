# MPI

---

### 1. Compilar utilizando OpenMPI

```bash
mpicc arquivo -o arquivoMPI
```

Este comando é utilizado para compilar um programa escrito em C que utiliza a biblioteca MPI (Message Passing Interface). O comando `mpicc` é o compilador específico para programas MPI. O parâmetro `arquivo` é o nome do arquivo fonte que você deseja compilar, e `-o arquivoMPI` especifica o nome do arquivo executável que será gerado após a compilação.

**Exemplo:**

Se você tiver um arquivo fonte chamado `programa.c`, você pode compilá-lo com o seguinte comando:

```bash
mpicc programa.c -o programaMPI
```

Isso gerará um arquivo executável chamado `programaMPI`.

**Curiosidade:**

O OpenMPI é uma implementação de código aberto da especificação MPI. Ele é amplamente utilizado em ambientes de computação de alto desempenho (HPC) devido à sua eficiência e flexibilidade.

### 2. Executar utilizando OpenMPI

```bash
mpirun -np <n_processos> executavel <args>
```

Este comando é utilizado para executar um programa MPI. O comando `mpirun` é o lançador de programas MPI. O parâmetro `-np <n_processos>` especifica o número de processos que serão utilizados para executar o programa. O parâmetro `executavel` é o nome do arquivo executável que você deseja executar, e `<args>` são os argumentos que você deseja passar para o programa.

**Exemplo:**

Se você deseja executar o programa `programaMPI` com 4 processos, você pode usar o seguinte comando:

```bash
mpirun -np 4 programaMPI
```

**Curiosidade:**

O `mpirun` é um comando poderoso que permite a execução de programas MPI em ambientes distribuídos, facilitando a paralelização de tarefas em múltiplos nós de um cluster.

### Execução em diversos hosts

```bash
mpirun -host <ip_host>, ... ,<ip_hostn> executavel <args>
```

Este comando é utilizado para executar um programa MPI em vários hosts (máquinas). O parâmetro `-host <ip_host>, ... ,<ip_hostn>` especifica os endereços IP dos hosts onde o programa será executado. O parâmetro `executavel` é o nome do arquivo executável que você deseja executar, e `<args>` são os argumentos que você deseja passar para o programa.

**Exemplo:**

Se você deseja executar o programa `programaMPI` em três hosts com os endereços IP `192.168.1.1`, `192.168.1.2` e `192.168.1.3`, você pode usar o seguinte comando:

```bash
mpirun -host 192.168.1.1,192.168.1.2,192.168.1.3 programaMPI
```

### Configurar em hostfile

Para configurar a execução em diversos hosts utilizando um arquivo de hostfile, siga os passos abaixo:

1. Crie um arquivo de texto chamado `hostfile` com a lista de hosts onde o programa será executado. Cada linha do arquivo deve conter o endereço IP ou o nome do host. Por exemplo:

   ```
   hostfile:
   192.168.1.1
   192.168.1.2
   192.168.1.3
   ```

2. Utilize o comando `mpirun` com a opção `-hostfile` para especificar o arquivo de hostfile:

   ```bash
   mpirun -hostfile hostfile -np <n_processos> executavel <args>
   ```

   Este comando executará o programa MPI nos hosts especificados no arquivo `hostfile`, utilizando o número de processos especificado por `-np <n_processos>`.

**Exemplo:**

Se você deseja executar o programa `programaMPI` com 6 processos nos hosts especificados no arquivo `hostfile`, você pode usar o seguinte comando:

```bash
mpirun -hostfile hostfile -np 6 programaMPI
```

### -oversubscribe: Permite disparar um número maior de processos do que o número de núcleos do processador.

Este parâmetro permite que você execute mais processos do que o número de núcleos disponíveis no processador. Isso pode ser útil em situações onde você deseja maximizar o uso dos recursos disponíveis, mesmo que isso possa levar a uma sobrecarga do sistema.

**Exemplo:**

Se você deseja executar o programa `programaMPI` com 8 processos em uma máquina com apenas 4 núcleos, você pode usar o seguinte comando:

```bash
mpirun -np 8 --oversubscribe programaMPI
```

### Rotinas Básicas:

Estas são algumas das rotinas básicas da biblioteca MPI:

- **MPI_Init:** Inicializa o ambiente MPI. Deve ser chamada no início do programa.
- **MPI_Comm_size:** Retorna o número total de processos no comunicador.
- **MPI_Comm_rank:** Retorna o identificador (rank) do processo chamador no comunicador.
- **MPI_Send:** Envia uma mensagem para outro processo.
- **MPI_Recv:** Recebe uma mensagem de outro processo.
- **MPI_Finalize:** Finaliza o ambiente MPI. Deve ser chamada no final do programa.

**Exemplo:**

Aqui está um exemplo simples de um programa MPI em C:

```c
#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    printf("Hello from process %d of %d\n", rank, size);

    MPI_Finalize();
    return 0;
}
```

Este programa imprime uma mensagem de cada processo, mostrando seu rank e o número total de processos.

**Curiosidade:**

A biblioteca MPI é uma das mais utilizadas para programação paralela em ambientes distribuídos. Ela permite que múltiplos processos em diferentes máquinas comuniquem-se e sincronizem-se de maneira eficiente, facilitando a resolução de problemas complexos que requerem grande poder de processamento.

---
