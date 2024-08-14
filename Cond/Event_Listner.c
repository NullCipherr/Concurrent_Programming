#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define TIME_EVENT 3 // Define o tempo ao qual é disparado um evento, em nosso caso, 3 segundos.

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t event = PTHREAD_COND_INITIALIZER;
int event_occurred = 0;

void* event_listener(void* arg) 
{
    while (1) 
    {
        pthread_mutex_lock(&mutex);
        
        while (!event_occurred) 
        {
            pthread_cond_wait(&event, &mutex);
        }
        
        printf("O evento foi disparado!\n");
        event_occurred = 0;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

// Função que gera um evento dado o tempo de eventos(TIME_EVENT)
void* event_generator(void* arg) 
{
    while (1) 
    {
        sleep(TIME_EVENT); // Simula um evento ocorrendo a cada 5 segundos
        pthread_mutex_lock(&mutex);
        event_occurred = 1;
        pthread_cond_signal(&event);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() 
{
    pthread_t listener, generator;
    
    pthread_create(&listener, NULL, event_listener, NULL);
    pthread_create(&generator, NULL, event_generator, NULL);
    
    pthread_join(listener, NULL);
    pthread_join(generator, NULL);
    
    return 0;
}