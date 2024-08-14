// Problema 2: Pontuação Compartilhada em um Jogo Cooperativo
//
// Descrição: Em um jogo cooperativo, os jogadores acumulam pontos em uma variável compartilhada. Cada vez que um jogador faz algo que gera pontos, ele adiciona à pontuação total. Queremos garantir que a pontuação não seja corrompida devido a acessos simultâneos.
// Objetivo : Implemente uma função que permita a vários jogadores atualizarem a pontuação compartilhada de forma segura, usando um mutex.

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_PLAYERS 5 // Número de jogadores

// Estrutura para representar um jogador
struct jogador
{
    int id;     // Identificador do jogador
    int pontos; // Pontos ganhos pelo jogador
};

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int pontuacao_total = 0;

void *ganhar_pontos(void *arg)
{
    struct jogador *jogador = (struct jogador *)arg;
    printf("Jogador %d ganhou %d pontos\n", jogador->id, jogador->pontos);

    // Implemente o controle de acesso à pontuação total aqui
    pthread_mutex_lock(&mutex);
    pontuacao_total += jogador->pontos;
    sleep(1); // Simula um tempo de processamento
    printf("Pontuação total: %d\n", pontuacao_total);
    pthread_mutex_unlock(&mutex); // Libera o acesso à pontuação total

    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_PLAYERS]; // Threads para os jogadores
    int pontos[NUM_PLAYERS] = {10, 20, 30, 40, 50};

    struct jogador jogadores[NUM_PLAYERS]; // Vetor de jogadores

    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        jogadores[i].id = i;
        jogadores[i].pontos = pontos[i];
        pthread_create(&threads[i], NULL, ganhar_pontos, &jogadores[i]); // Cria a thread para o jogador
    }

    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        pthread_join(threads[i], NULL); // Espera a thread terminar
    }

    pthread_mutex_destroy(&mutex); // Destrói o mutex

    return 0;
}