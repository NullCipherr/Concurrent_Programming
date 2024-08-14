// Problema 4: Controle de Acesso a um Baú do Tesouro
//
// Descrição : Em um jogo de aventura, há um baú do tesouro que contém itens valiosos.Apenas um jogador pode abrir o baú por vez.Se outro jogador tenta
// abrir o baú enquanto ele já está sendo acessado, deve esperar até que o baú esteja disponível novamente.
// Objetivo : Implemente uma função que permita a vários jogadores tentarem abrir o baú do tesouro, usando um mutex para controlar o acesso exclusivo.

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_PLAYERS 5 // Número de jogadores

pthread_mutex_t chest_mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex para controlar o acesso ao baú do tesouro

struct chest
{
    int id; // Identificador do baú
};

struct jogador
{
    int id;          // Identificador do jogador
    struct chest *c; // Baú do tesouro
};

void *abrir_bau(void *arg)
{
    struct jogador *jogador = (struct jogador *)arg;
    printf("Jogador %d está tentando abrir o baú do tesouro %d\n", jogador->id, jogador->c->id);

    pthread_mutex_lock(&chest_mutex); // Bloqueia o acesso ao baú

    printf("Jogador %d abriu o baú do tesouro %d\n", jogador->id, jogador->c->id);

    sleep(2); // Simula um tempo de processamento

    pthread_mutex_unlock(&chest_mutex); // Libera o acesso ao baú

    printf("Jogador %d fechou o baú do tesouro %d\n", jogador->id, jogador->c->id);

    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_PLAYERS]; // Threads para os jogadores
    struct chest c = {1};           // Baú do tesouro

    struct jogador jogadores[NUM_PLAYERS]; // Vetor de jogadores

    // Cria a thread para cada jogador
    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        jogadores[i].id = i;
        jogadores[i].c = &c;

        pthread_create(&threads[i], NULL, abrir_bau, &jogadores[i]);
    }

    // Espera as threads terminarem
    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}