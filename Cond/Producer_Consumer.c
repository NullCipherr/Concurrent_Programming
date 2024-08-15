#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int variavel_compartilhada = 0; // Variável compartilhada
pthread_mutex_t mutex;          // Mutex
pthread_cond_t cond;            // Variável de condição

void *produtor(void *arg)
{
    pthread_mutex_lock(&mutex); // Bloqueia o mutex
    int *id = (int *)arg;
    variavel_compartilhada++; // Incrementa a variável compartilhada
    printf("Produtor - Thread #%d - Incrementou a variavel compartilhada para %d\n", *id, variavel_compartilhada);
    pthread_cond_signal(&cond);   // Sinaliza a variável de condição
    pthread_mutex_unlock(&mutex); // Libera o mutex
    pthread_exit(NULL);
}

void *consumidor(void *arg)
{
    pthread_mutex_lock(&mutex); // Bloqueia o mutex
    int *id = (int *)arg;
    while (variavel_compartilhada == 0)
    {
        pthread_cond_wait(&cond, &mutex); // Aguarda a variável de condição
    }
    variavel_compartilhada--; // Decrementa a variável compartilhada
    printf("Consumidor - Thread #%d - Decrementou a variavel compartilhada para %d\n", *id, variavel_compartilhada);
    pthread_mutex_unlock(&mutex); // Libera o mutex
    pthread_exit(NULL);
}

int main()
{
    printf("Digite o número de threads produtoras: ");
    int num_produtoras;
    scanf("%d", &num_produtoras);

    printf("Digite o número de threads consumidoras: ");
    int num_consumidoras;
    scanf("%d", &num_consumidoras);

    pthread_t threads[num_produtoras + num_consumidoras];
    int thread_args[num_produtoras + num_consumidoras];

    pthread_mutex_init(&mutex, NULL); // Inicializa o mutex
    pthread_cond_init(&cond, NULL);   // Inicializa a variável de condição

    for (int i = 0; i < num_produtoras; i++)
    {
        printf("Criando thread produtora %d\n", i + 1);
        thread_args[i] = i + 1;
        pthread_create(&threads[i], NULL, produtor, &thread_args[i]);
    }

    for (int i = num_produtoras; i < num_produtoras + num_consumidoras; i++)
    {
        printf("Criando thread consumidora %d\n", i - num_produtoras + 1);
        thread_args[i] = i - num_produtoras + 1;
        pthread_create(&threads[i], NULL, consumidor, &thread_args[i]);
    }

    for (int i = 0; i < num_produtoras + num_consumidoras; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex); // Destroi o mutex
    pthread_cond_destroy(&cond);   // Destroi a variável de condição

    printf("Thread principal - Variável compartilhada: %d\n", variavel_compartilhada);
    printf("Thread principal - Fim\n");

    return 0;
}