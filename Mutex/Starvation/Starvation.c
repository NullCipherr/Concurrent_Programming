// 1. Starvation
//
// Starvation, também conhecido como inanição, é uma condição em sistemas de computação, onde uma thread ou processo fica indefinidamente impedido de progredir porque não consegue obter os recursos necessários.
// Ocorre frequentemente em sistemas concorrentes, onde múltiplas threads competem por recursos limitados.

// 2. Origem do conceito
//
// O conceito de starvation foi introduzido por Edsger Dijkstra em 1965, em seu artigo "Solution of a Problem in Concurrent Programming Control".
// Surgindo nos primeiros dias da computação, quando os sistemas de tempo compartilhado começaram a ser desenvolvidos.
// Em um sistema de tempo compartilhado, múltiplos processos compartilham o tempo de CPU, e cada processo é executado por um curto período de tempo antes de ser interrompido para dar lugar a outro processo.
// A inanição era um problema comum, pois os sistemas não tinham mecanismos para evitar que um processo monopolizasse os recursos do sistema.

// 3. Causas de Starvation
//
// Alguns cenários comuns que podem levar à inanição incluem:
// 1. Prioridades de Threads : Threads com prioridades mais baixas podem ser impedidas de progredir se threads com prioridades mais altas monopolizarem os recursos.
// 2. Algoritmos de Escalonamento : Algoritmos de escalonamento que não garantem justiça podem levar à inanição, onde alguns processos são executados com mais frequência do que outros.
// 3. Constante Requisição de Recursos : Se uma thread solicitar um recurso com muita frequência, ela pode ser impedida de progredir se outras threads continuarem a adquirir o recurso.
// ETC...

// 4. Evitando Starvation
//
// Existem várias técnicas para evitar a inanição em sistemas concorrentes:
// 1. Prioridades Justas : Garantir que todas as threads tenham a oportunidade de adquirir recursos, independentemente de sua prioridade.
// 2. Limitação de Recursos : Limitar a quantidade de recursos que uma thread pode adquirir em um determinado período de tempo.
// 3. Escalonamento Round-Robin : Utilizar um algoritmo de escalonamento round-robin, onde cada thread é executada por um curto período de tempo antes de ser interrompida.
// 4. Escalonamento de Loteria : Utilizar um algoritmo de escalonamento de loteria, onde as threads são selecionadas aleatoriamente para receber recursos, distribuindo-os de forma mais justa.
// 5. Detecção de Deadlocks : Detectar e resolver deadlocks, que podem levar à inanição de outras threads.
// 6. Envelhecimento de Threads : Implementar um mecanismo de envelhecimento de threads, onde threads mais antigas têm prioridade mais alta para adquirir recursos.
// ETC...

// 5. Exemplo de Starvation - Escalonamento de CPU com Prioridades
// Imagine um sistema operacional que utiliza um algoritmo de escalonamento de CPU baseado em prioridades, onde threads com prioridades mais altas são executadas com mais frequência do que threads com prioridades mais baixas.
// Em nosso exemplo, as threads de prioridade mais alta estão constantemente recebendo o tempo de CPU, enquanto as threads de prioridade mais baixa esperam indefinidamente por sua vez.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define HIGH_PRIORITY_THREADS 5 // Número de threads de alta prioridade
#define LOW_PRIORITY_THREADS 1  // Número de threads de baixa prioridade

// Função executada pela thread de alta prioridade
void *high_priority_task(void *arg)
{
    while (1)
    {
        printf("Alta prioridade em execução\n");
        usleep(1000000); // Simula um trabalho
    }
    pthread_exit(NULL);
}

// Função executada pela thread de baixa prioridade
void *low_priority_task(void *arg)
{
    while (1)
    {
        printf("Baixa prioridade em execução\n");
        usleep(1000000); // Simula um trabalho
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t high_priority[HIGH_PRIORITY_THREADS]; // Threads de alta prioridade
    pthread_t low_priority[LOW_PRIORITY_THREADS];   // Threads de baixa prioridade

    // Cria threads de alta prioridade
    for (int i = 0; i < HIGH_PRIORITY_THREADS; i++)
    {
        pthread_create(&high_priority[i], NULL, high_priority_task, NULL);
    }

    // Cria threads de baixa prioridade
    for (int i = 0; i < LOW_PRIORITY_THREADS; i++)
    {
        pthread_create(&low_priority[i], NULL, low_priority_task, NULL);
    }

    // Espera as threads de alta prioridade terminarem
    for (int i = 0; i < HIGH_PRIORITY_THREADS; i++)
    {
        pthread_join(high_priority[i], NULL);
    }

    // Espera as threads de baixa prioridade terminarem
    for (int i = 0; i < LOW_PRIORITY_THREADS; i++)
    {
        pthread_join(low_priority[i], NULL);
    }

    return 0;
}