// Sincronização de Turnos em um Jogo de Tabuleiro
//
// Implemente um jogo de tabuleiro onde várias threads representam jogadores 
// que jogam em turnos. Use variáveis de condição para garantir que cada jogador 
// espere sua vez antes de fazer sua jogada

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_PLAYERS 10 // Número de jogadores.

int current_turn = 0 ;

pthread_mutex_t turn_mutex = PTHREAD_MUTEX_INITIALIZER ;
pthread_cond_t turn_cond = PTHREAD_COND_INITIALIZER ;

void *player_function(void *arg)
{
    int player_id = *(int *)arg;

    printf("O jogador %d está aguardando para realizar a sua jogada.\n", player_id) ;

    while(1)
    {
        pthread_mutex_lock(&turn_mutex) ;

        while(current_turn != player_id)
        {
            pthread_cond_wait(&turn_cond, &turn_mutex) ;
        }

        printf("O jogador %d está realizando um movimento no turno %d.\n", player_id, current_turn) ;

        current_turn = (current_turn + 1) % NUM_PLAYERS ; // Progride o turno.

        pthread_cond_broadcast(&turn_cond) ;
        pthread_mutex_unlock(&turn_mutex) ;

        sleep(1) ;
    }
    return NULL ;
}

int main()
{
    pthread_t players[NUM_PLAYERS] ; // Thread para jogadores
    int player_id[NUM_PLAYERS] ;

    for(int i = 0 ; i < NUM_PLAYERS; i++)
    {
        player_id[i] = i ;
        pthread_create(&players[i], NULL, player_function, &player_id[i]) ;
    }

    // Aguarda todas as threads terminarem
    for(int i = 0 ; i < NUM_PLAYERS; i++)
    {
        pthread_join(players[i], NULL) ;
    }

    printf("Todas os jogadores finalizaram o seu turno") ;

    return 0 ;
}