// Exercício - Restaurante com Filas de Prioridade
//
// Imagine um restaurante onde clientes VIPs têm prioridade sobre clientes normais, mas para evitar starvation dos clientes normais,
// o sistema deve garantir que após um certo número de clientes VIPs serem atendidos, pelo menos um cliente normal deve ser atendido.
// Implemente um sistema de filas com prioridade utilizando mutexes e variáveis de condição para garantir justiça.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define TIME 3000000 // Tempo de atendimento de um cliente

#define NUM_CUSTOMERS 13 // Número total de clientes
#define VIP_THRESHOLD 4  // Número de clientes VIPs atendidos antes de atender um cliente normal

pthread_mutex_t restaurant_mutex;
pthread_cond_t cond;
int vip_count = 0; // Número de clientes VIPs atendidos

void *customer_task(void *arg)
{
    int id = *(int *)arg;    // ID do cliente
    int is_vip = rand() % 2; // 0 para cliente normal, 1 para cliente VIP

    while (1)
    {
        pthread_mutex_lock(&restaurant_mutex);

        if (is_vip)
        {
            while (vip_count >= VIP_THRESHOLD)
            {
                pthread_cond_wait(&cond, &restaurant_mutex);
            }
            vip_count++;
            printf("Cliente VIP %d atendido\n", id);
        }
        else
        {
            while (vip_count < VIP_THRESHOLD)
            {
                pthread_cond_wait(&cond, &restaurant_mutex);
            }
            vip_count = 0;
            printf("Cliente %d atendido\n", id);
        }

        pthread_mutex_unlock(&restaurant_mutex);
        usleep(TIME);

        pthread_mutex_lock(&restaurant_mutex);
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&restaurant_mutex);

        usleep(TIME);
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t customer[NUM_CUSTOMERS];
    int customer_id[NUM_CUSTOMERS];

    pthread_mutex_init(&restaurant_mutex, NULL);
    pthread_cond_init(&cond, NULL);

    for (int i = 0; i < NUM_CUSTOMERS; i++)
    {
        customer_id[i] = i;
        pthread_create(&customer[i], NULL, customer_task, &customer_id[i]);
    }

    for (int i = 0; i < NUM_CUSTOMERS; i++)
    {
        pthread_join(customer[i], NULL);
    }

    pthread_mutex_destroy(&restaurant_mutex);
    pthread_cond_destroy(&cond);

    return 0;
}