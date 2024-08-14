// Problema 1: Controle de Acesso a uma Área Segura no Jogo
//
// Descrição : Em um jogo de mundo aberto, há uma "área segura" onde os jogadores podem entrar para recuperar energia sem serem atacados.Apenas um jogador pode estar na área segura ao mesmo tempo.
// Objetivo : Implemente uma função que permita a vários jogadores tentarem acessar a área segura.Use um mutex para garantir que apenas um jogador esteja na área segura por vez.

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_PLAYERS 5 // Número de jogadores
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Estrutura para representar um jogador
struct jogador
{
    int id;
    int health; // Barra de vida
};

// Função para simular o jogador acessando a área segura
void *acessar_area_segura(void *arg)
{
    struct jogador *jogador = (struct jogador *)arg;
    printf("Jogador %d está tentando acessar a área segura com %d de vida\n", jogador->id, jogador->health);

    // Implemente o controle de acesso à área segura aqui
    pthread_mutex_lock(&mutex);
    printf("Jogador %d entrou na área segura\n", jogador->id);

    // Recupera a vida do jogador
    while (jogador->health < 100)
    {
        if ((jogador->health + 10) >= 100)
        {
            jogador->health = 100;
            sleep(1);
            break;
        }
        else
        {
            jogador->health += 10;
            printf("Jogador %d recuperando vida, vida: %d\n", jogador->id, jogador->health);
            sleep(1);
        }
    }
    printf("Jogador %d saiu da área segura com %d de vida\n", jogador->id, jogador->health);
    pthread_mutex_unlock(&mutex); // Libera o acesso à área segura

    pthread_exit(NULL);
}

// Função para simular o jogador renascendo
void *renascer(void *arg)
{
    struct jogador *jogador = (struct jogador *)arg;
    printf("Jogador %d renasceu\n", jogador->id);
    jogador->health = 100;
    pthread_exit(NULL);
}

// Função para simular o jogador tomando dano
void *simula_tomar_dano(void *arg)
{
    struct jogador *jogador = (struct jogador *)arg;
    while (1)
    {
        // Simula o jogador tomando dano
        jogador->health -= 10;
        printf("Jogador %d tomou dano, vida: %d\n", jogador->id, jogador->health);
        sleep(1);

        // Caso o jogador tenha menos de 30 de vida, ele tenta acessar a área segura, caso contrário, ele continua tomando dano
        if (jogador->health <= 30)
        {
            pthread_t area_segura_thread;

            // O primeiro acessa a area segura, enquanto os outros esperam na fila
            if (pthread_create(&area_segura_thread, NULL, acessar_area_segura, jogador) == 0)
            {
                pthread_join(area_segura_thread, NULL);
            }
            else
            {
                printf("Jogador %d não conseguiu acessar a área segura e continua tomando dano\n", jogador->id);
            }
        }

        if (jogador->health <= 0)
        {
            printf("Jogador %d morreu\n", jogador->id);
            // Implemente o código para renascer o jogador
            pthread_t renascer_thread;
            pthread_create(&renascer_thread, NULL, renascer, jogador);
            pthread_join(renascer_thread, NULL);
        }

        // Simula um tempo de espera antes de tomar dano novamente
        usleep(10000); // 10 milissegundos
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_PLAYERS];        // Threads para os jogadores
    struct jogador jogadores[NUM_PLAYERS]; // Jogadores

    // Inicializa os jogadores
    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        jogadores[i].id = i;
        jogadores[i].health = 100;
    }

    // Cria threads para simular os jogadores tomando dano
    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        pthread_create(&threads[i], NULL, simula_tomar_dano, &jogadores[i]);
    }

    // Espera as threads terminarem
    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex); // Destrói o mutex

    return 0;
}