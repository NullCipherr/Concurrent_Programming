// Exercício - Controle de Tráfego com Semáforos
//
// Simule um cruzamento onde carros vindos de diferentes direções competem para passar.
// Para evitar que carros de uma direção específica fiquem famintos, implemente um sistema de controle de tráfego que garanta justiça no cruzamento.
// Utilize mutexes e variáveis de condição para gerenciar o tráfego de carros em um cruzamento, garantindo assim, que nenhuma direção fique faminta.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_CARS 50      // Número de carros
#define NUM_DIRECTIONS 4 // Número de direções

pthread_mutex_t traffic_mutex;          // Mutex para controle de acesso ao cruzamento
pthread_cond_t cond;                    // Variável de condição para controle de tráfego
int cars_waiting[NUM_DIRECTIONS] = {0}; // Carros esperando em cada direção
int current_direction = 0;              // Direção atual

/*
 * Função que retorna a próxima direção a ser liberada
 * @return int: Próxima direção
 */
int proxima_direcao()
{
    int max_waiting = 0;                     // Número máximo de carros esperando
    int proxima_direcao = current_direction; // Próxima direção a ser liberada

    // Encontra a direção com mais carros esperando
    for (int i = 0; i < NUM_DIRECTIONS; i++)
    {
        // Se a direção i tiver mais carros esperando que a direção atual, atualiza a direção a ser liberada
        if (cars_waiting[i] > max_waiting)
        {
            max_waiting = cars_waiting[i]; // Atualiza o número máximo de carros esperando
            proxima_direcao = i;           // Atualiza a próxima direção
        }
    }

    return proxima_direcao; // Retorna a próxima direção
}

/*
 * Função que simula a passagem de um carro pelo cruzamento
 * @param arg: Identificador do carro
 * @return NULL
 */
void *car(void *arg)
{
    int id = *(int *)arg;                    // Identificador do carro
    int direction = rand() % NUM_DIRECTIONS; // Direção do carro

    while (1)
    {
        pthread_mutex_lock(&traffic_mutex); // Bloqueia o mutex
        cars_waiting[direction]++;          // Incrementa o número de carros esperando na direção do carro

        while (current_direction != direction || cars_waiting[direction] == 0) // Enquanto a direção atual não for a do carro ou não houver carros esperando
        {
            pthread_cond_wait(&cond, &traffic_mutex); // Aguarda a liberação do cruzamento
        }

        cars_waiting[direction]--; // Decrementa o número de carros esperando na direção do carro
        printf("Carro %d da direção %d está passando. Carros esperando na direção %d: %d\n", id, direction, direction, cars_waiting[direction]);
        current_direction = proxima_direcao(); // Atualiza a direção atual

        pthread_cond_broadcast(&cond);        // Libera todos os carros
        pthread_mutex_unlock(&traffic_mutex); // Libera o mutex
        usleep(500000);                       // Simula tempo de passagem pelo cruzamento

        printf("Carro %d da direção %d passou\n", id, direction);

        usleep(1000000); // Espera antes de tentar passar novamente
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t cars[NUM_CARS]; // Thread para cada carro
    int car_ids[NUM_CARS];    // Identificador de cada carro

    pthread_mutex_init(&traffic_mutex, NULL); // Inicializa o mutex
    pthread_cond_init(&cond, NULL);           // Inicializa a variável de condição

    // Inicializa as threads
    for (int i = 0; i < NUM_CARS; i++)
    {
        car_ids[i] = i;                                           // Identificador do carro
        pthread_create(&cars[i], NULL, car, (void *)&car_ids[i]); // Cria a thread
    }

    // Espera as threads terminarem
    for (int i = 0; i < NUM_CARS; i++)
    {
        pthread_join(cars[i], NULL);
    }

    pthread_mutex_destroy(&traffic_mutex); // Destrói o mutex
    pthread_cond_destroy(&cond);           // Destrói a variável de condição

    return 0;
}