// Sincronização de Movimentos de Jogadores
//
// Exercício : Em um jogo multiplayer, é necessário sincronizar os movimentos dos jogadores para evitar que eles se movam para a mesma posição no mapa ao mesmo tempo.

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define MAP_SIZE 100  // Tamanho do mapa
#define NUM_PLAYERS 9 // Número de jogadores

pthread_mutex_t map_mutex[MAP_SIZE][MAP_SIZE]; // Mutex para controlar o acesso ao mapa

// Estrutura que representa a posição de um jogador no mapa
typedef struct
{
    int x, y; // Posição do jogador no mapa
} Position;

Position players[NUM_PLAYERS]; // Posição dos jogadores

// Função que simula o movimento de um jogador
void *movePlayer(void *arg)
{
    int id = *(int *)arg;
    printf("Jogador %d está se movendo\n", id);

    // Bloqueia o acesso à posição do jogador
    pthread_mutex_lock(&map_mutex[players[id].x][players[id].y]);

    // Simula um tempo de movimento
    sleep(1);

    // Move o jogador
    players[id].x = rand() % MAP_SIZE;
    players[id].y = rand() % MAP_SIZE;
    printf("\nJogador %d se moveu para a posição (%d, %d)\n", id, players[id].x, players[id].y);

    // Libera o acesso à posição do jogador
    pthread_mutex_unlock(&map_mutex[players[id].x][players[id].y]);

    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_PLAYERS];
    int ids[NUM_PLAYERS];

    // Inicializa a posição dos jogadores
    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        players[i].x = rand() % MAP_SIZE; // Posição x aleatória no mapa
        players[i].y = rand() % MAP_SIZE; // Posição y aleatória no mapa
    }

    // Inicializa os mutexes do mapa
    for (int i = 0; i < MAP_SIZE; i++)
    {
        for (int j = 0; j < MAP_SIZE; j++)
        {
            pthread_mutex_init(&map_mutex[i][j], NULL); // Inicializa o mutex
        }
    }

    // Cria as threads dos jogadores
    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        ids[i] = i;
        pthread_create(&threads[i], NULL, movePlayer, &ids[i]);
    }

    // Aguarda as threads terminarem
    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Libera os mutexes do mapa
    for (int i = 0; i < MAP_SIZE; i++)
    {
        for (int j = 0; j < MAP_SIZE; j++)
        {
            pthread_mutex_destroy(&map_mutex[i][j]); // Destrói o mutex
        }
    }

    return 0;
}