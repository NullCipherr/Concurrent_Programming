// 1. Controle de Inventário de Itens
//
// Exercício : Em um jogo de RPG, diferentes threads representam jogadores que adicionam e removem itens de um inventário compartilhado.
// Use múltiplos mutexes para garantir que o inventário seja atualizado corretamente sem interferências de outras threads.

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_ITEMS 10 // Número máximo de itens no inventário

int inventory[MAX_ITEMS]; // Inventário de itens
int items_count = 0;      // Contador de itens no inventário

pthread_mutex_t add_mutex;    // Mutex para adicionar itens
pthread_mutex_t remove_mutex; // Mutex para remover itens

struct jogador
{
    int id;     // Identificador do jogador
    char *name; // Nome do jogador
};

void *addItem(void *arg)
{
    char *name = ((struct jogador *)arg)->name;
    int id = ((struct jogador *)arg)->id;
    pthread_mutex_lock(&add_mutex); // Bloqueia o acesso ao inventário

    // Se o inventário não estiver cheio, adiciona um item
    if (items_count < MAX_ITEMS)
    {
        inventory[items_count] = 1; // Adiciona um item -> 1 representa um item, ou pode ser um ponteiro para um item, identificador, etc.
        items_count++;              // Incrementa o contador de itens
        printf("Item adicionado ao inventário por %s_%d. Itens no inventário: %d\n", name, id, items_count);
    }
    else
    {
        printf("Inventário cheio. Não é possível adicionar mais itens.\n");
    }

    pthread_mutex_unlock(&add_mutex); // Libera o acesso ao inventário
    pthread_exit(NULL);               // Encerra a thread
}

void *removeItem(void *arg)
{
    char *name = ((struct jogador *)arg)->name;
    int id = ((struct jogador *)arg)->id;
    pthread_mutex_lock(&remove_mutex); // Bloqueia o acesso ao inventário

    // Se o inventário não estiver vazio, remove um item
    if (items_count > 0)
    {
        inventory[items_count - 1] = 0; // Remove um item -> 0 representa nenhum item
        items_count--;                  // Decrementa o contador de itens
        printf("Item removido do inventário por %s_%d. Itens no inventário: %d\n\n", name, id, items_count);
    }
    else
    {
        printf("Inventário vazio. Não é possível remover mais itens.\n");
    }

    pthread_mutex_unlock(&remove_mutex); // Libera o acesso ao inventário
    pthread_exit(NULL);                  // Encerra a thread
}

int main()
{
    printf("Digite o número de jogadores: ");
    int num_players;
    scanf("%d", &num_players);

    pthread_t threads[num_players]; // Threads para os jogadores
    struct jogador players[num_players];

    pthread_mutex_init(&add_mutex, NULL);    // Inicializa o mutex para adicionar itens. OBS: Pode ser o mesmo mutex, mas para fins didáticos, foi separado.
    pthread_mutex_init(&remove_mutex, NULL); // Inicializa o mutex para remover itens. OBS: Pode ser o mesmo mutex, mas para fins didáticos, foi separado.

    // Cria a thread para cada jogador
    for (int i = 0; i < num_players; i++)
    {
        if (i % 2 == 0)
        {
            players[i].id = i;
            players[i].name = "Kaddinton";
            pthread_create(&threads[i], NULL, addItem, &players[i]);
        }
        else
        {
            players[i].id = i;
            players[i].name = "Removertron";
            pthread_create(&threads[i], NULL, removeItem, &players[i]);
        }
    }

    // Espera as threads terminarem
    for (int i = 0; i < num_players; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&add_mutex);    // Destrói o mutex para adicionar itens
    pthread_mutex_destroy(&remove_mutex); // Destrói o mutex para remover itens

    return 0;
}