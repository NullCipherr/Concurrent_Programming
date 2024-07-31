// Exercicio - Elevador inteligente
//
// Implemente um sistema de controle para um elevador em um prédio de vários andares.
// Use mutexes para controlar o acesso ao elevador e implemente uma estratégia para evitar
// starvation, garantindo que pessoas esperando em andares menos movimentados também sejam atendidas em um tempo razoável

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_FLOORS 5 // Número de andares
#define NUM_PEOPLE 2 // Número de pessoas

pthread_mutex_t elevator_mutex;           // Mutex para controle de acesso ao elevador
pthread_cond_t cond[NUM_FLOORS];          // Variável de condição para cada andar
int people_waiting[NUM_FLOORS] = {0};     // Pessoas esperando em cada andar
int current_floor = 0;                    // Andar atual
int elevator_direction = 1;               // Direção do elevador (1 = subindo, -1 = descendo)
int people_in_elevator[NUM_FLOORS] = {0}; // Pessoas dentro do elevador para cada andar

void *person_task(void *arg)
{
    int id = *(int *)arg;                  // Identificador da pessoa
    int start_floor = rand() % NUM_FLOORS; // Andar de origem da pessoa
    int dest_floor;                        // Andar de destino da pessoa

    do
    {
        dest_floor = rand() % NUM_FLOORS; // Andar de destino da pessoa
    } while (dest_floor == start_floor); // Garante que o andar de destino é diferente do andar de origem

    pthread_mutex_lock(&elevator_mutex); // Bloqueia o mutex
    people_waiting[start_floor]++;       // Incrementa o número de pessoas esperando no andar de origem

    while (current_floor != start_floor) // Enquanto o elevador não estiver no andar de origem
    {
        pthread_cond_wait(&cond[start_floor], &elevator_mutex); // Aguarda a chegada do elevador
    }

    people_waiting[start_floor]--;    // Decrementa o número de pessoas esperando no andar de origem
    people_in_elevator[dest_floor]++; // Incrementa o número de pessoas no elevador que vão para o andar de destino
    printf("Pessoa %d entrou no elevador no andar %d indo para o andar %d\n", id, start_floor, dest_floor);

    while (current_floor != dest_floor) // Enquanto o elevador não estiver no andar de destino
    {
        pthread_cond_wait(&cond[dest_floor], &elevator_mutex); // Aguarda a chegada do elevador
    }

    people_in_elevator[dest_floor]--;                                   // Decrementa o número de pessoas no elevador que vão para o andar de destino
    printf("Pessoa %d saiu do elevador no andar %d\n", id, dest_floor); // Pessoa chegou ao andar de destino
    pthread_mutex_unlock(&elevator_mutex);                              // Libera o mutex

    return NULL;
}

void *elevator(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&elevator_mutex); // Bloqueia o mutex

        printf("Elevador no andar %d\n", current_floor);
        pthread_cond_broadcast(&cond[current_floor]); // Libera todas as pessoas no andar atual

        // Verifica se o elevador chegou ao térreo ou ao último andar
        if (current_floor == 0)
        {
            elevator_direction = 1; // Sobe
        }
        else if (current_floor == NUM_FLOORS - 1)
        {
            elevator_direction = -1; // Desce
        }

        // Move o elevador para o próximo andar
        current_floor += elevator_direction;

        pthread_mutex_unlock(&elevator_mutex); // Libera o mutex
        sleep(2);                              // Aguarda um tempo para simular a movimentação do elevador
    }

    return NULL;
}

int main()
{
    pthread_t person[NUM_PEOPLE], elevator_thread; // Thread para cada pessoa e para o elevador
    int id_person[NUM_PEOPLE];                     // Identificador de cada pessoa

    pthread_mutex_init(&elevator_mutex, NULL); // Inicializa o mutex

    // Inicializa as variáveis de condição para cada andar
    for (int i = 0; i < NUM_FLOORS; i++)
    {
        pthread_cond_init(&cond[i], NULL);
    }

    pthread_create(&elevator_thread, NULL, elevator, NULL); // Cria a thread do elevador

    // Inicializa as threads das pessoas
    for (int i = 0; i < NUM_PEOPLE; i++)
    {
        id_person[i] = i;                                             // Identificador da pessoa
        pthread_create(&person[i], NULL, person_task, &id_person[i]); // Cria a thread
    }

    // Aguarda as threads terminarem
    for (int i = 0; i < NUM_PEOPLE; i++)
    {
        pthread_join(person[i], NULL);
    }

    return 0;
}