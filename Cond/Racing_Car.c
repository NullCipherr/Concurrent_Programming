// Sincronização de Eventos em um Jogo de Corrida
//
// Implemente um jogo de corrida onde várias threads representam carros que 
// competem em uma pista. Use variáveis de condição para sincronizar o início 
// da corrida e o fim da corrida.

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_CARS 10

pthread_mutex_t race_mutex = PTHREAD_MUTEX_INITIALIZER ;
pthread_cond_t race_start = PTHREAD_COND_INITIALIZER ;
pthread_cond_t race_end = PTHREAD_COND_INITIALIZER ;

int race_started = 0 ;
int race_finished = 0 ;

void *car_race(void *arg)
{
    int id_car = *(int *)arg ;

    pthread_mutex_lock(&race_mutex) ;
    
    // Enquanto a corrida não começa
    while(!race_started)
    {
        pthread_cond_wait(&race_start, &race_mutex) ;
    }
    pthread_mutex_unlock(&race_mutex) ;

    printf("O carro %d iniciou a corrida.\n", id_car) ;

    sleep(rand() % NUM_CARS + 1) ; // Tempo de corrida é simulado.

    printf("O carro %d finalizou a corrida.\n", id_car) ;

    pthread_mutex_lock(&race_mutex) ;
    race_finished++ ;

    // Se todos os carros finalizaram a corrida, então
    if(race_finished == NUM_CARS)
    {
        pthread_cond_broadcast(&race_end) ;
    }

    pthread_mutex_unlock(&race_mutex) ;
    pthread_exit(NULL) ;
}

int main()
{
    pthread_t car[NUM_CARS] ;
    int car_id[NUM_CARS] ;
    
    for(int i = 0 ; i < NUM_CARS; i++)
    {
        car_id[i] = i ;
        pthread_create(&car[i], NULL, car_race, &car_id[i]) ;
    }

    sleep(1); // Simula o tempo antes do início da corrida
    
    pthread_mutex_lock(&race_mutex);
    race_started = 1;
    pthread_cond_broadcast(&race_start);
    pthread_mutex_unlock(&race_mutex);

    pthread_mutex_lock(&race_mutex);
    
    while (!race_finished) 
    {
        pthread_cond_wait(&race_end, &race_mutex);
    }
    
    pthread_mutex_unlock(&race_mutex);

    printf("A corrida acabou.\n");

    for (int i = 0; i < NUM_CARS; i++) {
        pthread_join(car[i], NULL);
    }

    return 0 ;
}

