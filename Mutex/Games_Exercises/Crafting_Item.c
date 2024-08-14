// Problema 3: Produção de Itens em um Jogo de Crafting
//
// Descrição : Em um jogo de crafting, vários jogadores podem criar itens usando um conjunto de recursos compartilhados. Cada item custa uma certa quantidade de recursos para ser produzido.Queremos garantir
// que os recursos não sejam usados simultaneamente de forma que resultem em uma contagem incorreta.
// Objetivo : Implemente uma função que permita a vários jogadores criarem itens, consumindo recursos compartilhados de forma segura, usando um mutex.

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_PLAYERS 5 // Número de jogadores

struct jogador
{
    int id;    // Identificador do jogador
    int custo; // Custo do item
};

pthread_mutex_t recursos_mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex para controlar o acesso aos recursos
int recursos_disponiveis = 100;                             // Recursos disponíveis

// Função para criar um item
void *craft_item(void *arg)
{
    struct jogador *jogador = (struct jogador *)arg;
    printf("Jogador %d está criando um item que custa %d recursos\n", jogador->id, jogador->custo);

    pthread_mutex_lock(&recursos_mutex); // Bloqueia o acesso aos recursos

    sleep(2); // Simula um tempo de processamento

    // Implemente o controle de acesso aos recursos aqui
    if (recursos_disponiveis >= jogador->custo)
    {
        recursos_disponiveis -= jogador->custo;
        printf("Item criado com sucesso! Recursos restantes: %d\n", recursos_disponiveis);
    }
    else
    {
        printf("Recursos insuficientes para criar o item\n");
    }
    pthread_mutex_unlock(&recursos_mutex); // Libera o acesso aos recursos

    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_PLAYERS];                 // Threads para os jogadores
    int custos[NUM_PLAYERS] = {10, 20, 30, 40, 50}; // Custo de cada item

    struct jogador jogadores[NUM_PLAYERS]; // Vetor de jogadores

    // Cria a thread para cada jogador
    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        jogadores[i].id = i;
        jogadores[i].custo = custos[i];

        pthread_create(&threads[i], NULL, craft_item, &jogadores[i]);
    }

    // Espera as threads terminarem
    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&recursos_mutex); // Destrói o mutex

    return 0;
}