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

O OpenMPI é uma implementação de código aberto da especificação MPI. Ele é amplamente utilizado em ambientes de computação de alto desempenho (HPC) devido à sua eficiência e flexibilidade. O OpenMPI suporta uma ampla gama de arquiteturas e sistemas operacionais, tornando-o uma escolha popular para desenvolvedores de software paralelo.

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

O `mpirun` é um comando poderoso que permite a execução de programas MPI em ambientes distribuídos, facilitando a paralelização de tarefas em múltiplos nós de um cluster. Ele suporta várias opções para configurar a execução, como especificar hosts, definir variáveis de ambiente e controlar o mapeamento de processos.

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

**Curiosidade:**

A opção --oversubscribe é particularmente útil em ambientes onde os recursos de computação são limitados, mas a carga de trabalho é alta. No entanto, é importante monitorar o desempenho do sistema para garantir que a sobrecarga não cause degradação significativa na performance.

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

A biblioteca MPI é uma das mais utilizadas para programação paralela em ambientes distribuídos. Ela permite que múltiplos processos em diferentes máquinas comuniquem-se e sincronizem-se de maneira eficiente, facilitando a resolução de problemas complexos que requerem grande poder de processamento. A MPI é amplamente utilizada em áreas como simulações científicas, análise de dados e processamento de imagens.

Claro, vamos continuar expandindo o conteúdo a partir da seção de comunicação coletiva, adicionando mais exemplos, detalhes e curiosidades.

## Conceitos Intermediário

### Comunicação Ponto a Ponto

A comunicação ponto a ponto é uma das formas mais básicas de comunicação em MPI. Ela envolve a troca de mensagens entre dois processos específicos.

```c
#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        int message = 42;
        MPI_Send(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent message %d to process 1\n", message);
    } else if (rank == 1) {
        int message;
        MPI_Recv(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received message %d from process 0\n", message);
    }

    MPI_Finalize();
    return 0;
}
```

### Comunicação Coletiva

A comunicação coletiva envolve a troca de mensagens entre todos os processos em um comunicador. Exemplos de operações coletivas incluem `MPI_Bcast`, `MPI_Scatter`, `MPI_Gather` e `MPI_Reduce`. Essas operações são essenciais para coordenar e sincronizar a comunicação entre múltiplos processos em um ambiente paralelo.

#### MPI_Bcast

A função `MPI_Bcast` (Broadcast) é usada para enviar dados de um processo (root) para todos os outros processos no comunicador.

**Exemplo:**

```c
#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int data;
    if (rank == 0) {
        data = 42;
    }

    MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Process %d received data: %d\n", rank, data);

    MPI_Finalize();
    return 0;
}
```

Neste exemplo, o processo 0 (root) envia o valor `42` para todos os outros processos no comunicador. Todos os processos recebem o valor e o imprimem.

#### MPI_Scatter

A função `MPI_Scatter` é usada para distribuir dados de um processo (root) para todos os outros processos no comunicador. Cada processo recebe uma parte dos dados.

**Exemplo:**

```c
#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int data[4];
    int recv_data;

    if (rank == 0) {
        for (int i = 0; i < size; i++) {
            data[i] = i * 10;
        }
    }

    MPI_Scatter(data, 1, MPI_INT, &recv_data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Process %d received data: %d\n", rank, recv_data);

    MPI_Finalize();
    return 0;
}
```

Neste exemplo, o processo 0 (root) distribui um array de dados para todos os outros processos. Cada processo recebe um elemento do array e o imprime.

#### MPI_Gather

A função `MPI_Gather` é usada para coletar dados de todos os processos no comunicador e enviá-los para um processo (root).

**Exemplo:**

```c
#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int send_data = rank * 10;
    int recv_data[4];

    MPI_Gather(&send_data, 1, MPI_INT, recv_data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Process 0 received data: ");
        for (int i = 0; i < size; i++) {
            printf("%d ", recv_data[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
```

Neste exemplo, cada processo envia um valor para o processo 0 (root), que coleta todos os valores em um array e os imprime.

#### MPI_Reduce

A função `MPI_Reduce` é usada para realizar uma operação de redução (como soma, máximo, mínimo) em dados de todos os processos no comunicador e enviar o resultado para um processo (root).

**Exemplo:**

```c
#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int data = rank * 10;
    int result;

    MPI_Reduce(&data, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Sum of all data: %d\n", result);
    }

    MPI_Finalize();
    return 0;
}
```

Neste exemplo, cada processo envia um valor para o processo 0 (root), que calcula a soma de todos os valores e imprime o resultado.

### Comunicação Não Bloqueante

A comunicação não bloqueante permite que os processos continuem executando outras operações enquanto aguardam a conclusão de uma operação de comunicação. Isso pode melhorar a eficiência e o desempenho do programa.

#### MPI_Isend e MPI_Irecv

As funções `MPI_Isend` e `MPI_Irecv` são usadas para enviar e receber mensagens de forma não bloqueante.

**Exemplo:**

```c
#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Request request;
    MPI_Status status;

    if (rank == 0) {
        int message = 42;
        MPI_Isend(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
        printf("Process 0 sent message %d to process 1\n", message);
    } else if (rank == 1) {
        int message;
        MPI_Irecv(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
        printf("Process 1 received message %d from process 0\n", message);
    }

    MPI_Finalize();
    return 0;
}
```

Neste exemplo, o processo 0 envia uma mensagem para o processo 1 de forma não bloqueante. Ambos os processos continuam executando outras operações enquanto aguardam a conclusão da comunicação.

### Comunicação Coletiva Não Bloqueante

A comunicação coletiva não bloqueante permite que os processos continuem executando outras operações enquanto aguardam a conclusão de uma operação coletiva.

#### MPI_Ibcast

A função `MPI_Ibcast` é usada para enviar dados de um processo (root) para todos os outros processos no comunicador de forma não bloqueante.

**Exemplo:**

```c
#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int data;
    MPI_Request request;
    MPI_Status status;

    if (rank == 0) {
        data = 42;
    }

    MPI_Ibcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD, &request);
    MPI_Wait(&request, &status);

    printf("Process %d received data: %d\n", rank, data);

    MPI_Finalize();
    return 0;
}
```

Neste exemplo, o processo 0 (root) envia o valor `42` para todos os outros processos no comunicador de forma não bloqueante. Todos os processos recebem o valor e o imprimem.

### Comunicação em Grupos e Comunicadores

A MPI permite a criação de grupos e comunicadores para facilitar a comunicação entre subconjuntos de processos.

#### MPI_Comm_create

A função `MPI_Comm_create` é usada para criar um novo comunicador a partir de um comunicador existente.

**Exemplo:**

```c
#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Group world_group;
    MPI_Comm_group(MPI_COMM_WORLD, &world_group);

    int ranks[2] = {0, 1};
    MPI_Group new_group;
    MPI_Group_incl(world_group, 2, ranks, &new_group);

    MPI_Comm new_comm;
    MPI_Comm_create(MPI_COMM_WORLD, new_group, &new_comm);

    if (new_comm != MPI_COMM_NULL) {
        int new_rank;
        MPI_Comm_rank(new_comm, &new_rank);
        printf("Process %d has new rank %d in the new communicator\n", rank, new_rank);
    }

    MPI_Group_free(&world_group);
    MPI_Group_free(&new_group);
    if (new_comm != MPI_COMM_NULL) {
        MPI_Comm_free(&new_comm);
    }

    MPI_Finalize();
    return 0;
}
```

Neste exemplo, um novo comunicador é criado a partir do comunicador `MPI_COMM_WORLD`, incluindo apenas os processos com rank 0 e 1. Os processos no novo comunicador imprimem seus novos ranks.

---
