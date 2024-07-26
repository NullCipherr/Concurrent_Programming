// 1. Envelhecimento(Aging)
//
// A técnica de envelhecimento é uma abordagem para evitar a inanição em sistemas concorrentes, onde threads mais antigas têm prioridade mais alta para adquirir recursos.
// Isso ajuda a garantir que todas as threads tenham a oportunidade de progredir, independentemente de sua prioridade inicial.
//
// 2. Implementação do Envelhecimento
//
// O envelhecimento pode ser implementado atribuindo uma pontuação de prioridade a cada thread com base em sua idade.
// Threads mais antigas recebem uma pontuação de prioridade mais alta, o que aumenta sua probabilidade de adquirir recursos.
// A pontuação de prioridade pode ser atualizada periodicamente para garantir que as threads mais antigas tenham prioridade mais alta.

// 3. Exericio
// Modifique o exemplo de escalonamento de CPU com prioridades para incluir um mecanismo de envelhecimento de threads.
// Garantindo que threads de baixa prioridade eventualmente recebam tempo de CPU, mesmo que haja threads de alta prioridade em execução.

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
        usleep(100000); // Simula um trabalho
    }
    pthread_exit(NULL);
}

// Função executada pela thread de baixa prioridade
void *low_priority_task(void *arg)
{
    int priority = 0; // Prioridade da thread

    while (1)
    {
        if (priority > 5)
        {
            printf("Baixa prioridade em execução\n");
            priority = 0;
            usleep(100000); // Simula um trabalho
        }
        else
        {
            priority++;
        }
        usleep(100000); // Simula um trabalho
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
