// Gerenciamento de Recursos Compartilhados
// Exercício : Em um jogo de estratégia, jogadores(threads) competem por recursos limitados, como ouro e madeira.
// Utilize múltiplos mutexes para controlar o acesso a esses recursos.

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_PLAYER 10 // Número máximo de jogadores

#define MAX_GOLD 20  // Ouro máximo da partida
#define MAX_WOOD 100 // Madeira máxima da partida

pthread_mutex_t gold_mutex; // Mutex para controlar o acesso ao ouro
pthread_mutex_t wood_mutex; // Mutex para controlar o acesso à madeira

struct player
{
    int id;   // Identificador do jogador
    int gold; // Ouro do jogador
    int wood; // Madeira do jogador
};

void *collect_resources(void *arg)
{
    struct player *player = (struct player *)arg;
    printf("Jogador %d está indo coletar recursos\n", player->id);

    // Bloqueia o acesso ao ouro
    pthread_mutex_lock(&gold_mutex);
    // Bloqueia o acesso à madeira
    pthread_mutex_lock(&wood_mutex);

    // Simula um tempo de coleta
    sleep(3);

    // Coleta recursos
    if (player->gold < MAX_GOLD)
    {
        player->gold += 10;
        printf("Jogador %d coletou 10 de ouro. Ouro do jogador: %d\n", player->id, player->gold);
    }
    else
    {
        printf("Ouro máximo atingido. Não é possível coletar mais ouro.\n");
    }

    if (player->wood < MAX_WOOD)
    {
        player->wood += 10;
        printf("Jogador %d coletou 10 de madeira. Madeira do jogador: %d\n", player->id, player->wood);
    }
    else
    {
        printf("Madeira máxima atingida. Não é possível coletar mais madeira.\n");
    }

    // Libera o acesso à madeira
    pthread_mutex_unlock(&wood_mutex);
    // Libera o acesso ao ouro
    pthread_mutex_unlock(&gold_mutex);

    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[MAX_PLAYER]; // Threads para os jogadores

    struct player players[MAX_PLAYER]; // Vetor de jogadores

    // Inicializa os mutexes
    pthread_mutex_init(&gold_mutex, NULL);
    pthread_mutex_init(&wood_mutex, NULL);

    // Cria a thread para cada jogador
    for (int i = 0; i < MAX_PLAYER; i++)
    {
        players[i].id = i;
        players[i].gold = 0;
        players[i].wood = 0;

        pthread_create(&threads[i], NULL, collect_resources, &players[i]);
    }

    // Espera as threads terminarem
    for (int i = 0; i < MAX_PLAYER; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}