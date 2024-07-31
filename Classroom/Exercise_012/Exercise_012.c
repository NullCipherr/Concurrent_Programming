// Aluno e RA
// Andrei Roberto da Costa RA: 107975

/*

Exemplo 15: Implementacao do desafio do Exemplo 14, ou seja, problema do
produtor-consumidor usando mutex.

Desafio: melhore o programa usando semaforos para controlar a ocupacao
do buffer, bem como para controlar o numero de producoes e de consumos
faltantes para encerrar a aplicacao.

Observe os seguintes tipos e funcoes que podem ser usados:

sem_t
sem_init( )
sem_wait( )
sem_post( )
sem_trywait( )

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#define maxBuffer 10000
#define maxNumero 10000
#define maxThread 300

typedef struct
{
    int buffer[maxBuffer]; // local de armazenamento circular
    int in,                // posicao de insercao
        out,               // posicao de retirada
        count,             // quantidade de elementos no buffer
        tam;               // tamanho util do buffer
} tBuffer;

tBuffer buffer;

int nProd, // quantidade de dados a serem fabricados (producoes)
    nCons, // quantidade de dados a serem consumidos (consumos),
           // que nesta implementacao eh igual ao numero de producoes
    ntp,   // numero de threads produtoras
    ntc;   // numero de threads consumidoras

pthread_mutex_t inMutex = PTHREAD_MUTEX_INITIALIZER,
                outMutex = PTHREAD_MUTEX_INITIALIZER,
                countMutex = PTHREAD_MUTEX_INITIALIZER,
                nProdMutex = PTHREAD_MUTEX_INITIALIZER,
                nConsMutex = PTHREAD_MUTEX_INITIALIZER;

sem_t freeSpaces, itensInBuffer;

// inicializa a estrutura do buffer
void criaBuffer(int tam)
{
    buffer.in = -1;
    buffer.out = -1;
    buffer.count = 0;
    buffer.tam = tam;
}

// deposita o dado no buffer
int deposita(int dado)
{
    sem_wait(&freeSpaces);
    pthread_mutex_lock(&inMutex);

    buffer.in = (buffer.in + 1) % (buffer.tam);
    buffer.buffer[buffer.in] = dado;

    pthread_mutex_unlock(&inMutex);
    sem_post(&itensInBuffer);

    return 1;
}

// retira o dado do buffer
int retira(int *dado)
{
    sem_wait(&itensInBuffer);
    pthread_mutex_lock(&outMutex);

    buffer.out = (buffer.out + 1) % (buffer.tam);
    *dado = buffer.buffer[buffer.out];

    pthread_mutex_unlock(&outMutex);
    sem_post(&freeSpaces);

    return 1;
}

// lista os elementos do buffer
void mostraBuffer(void)
{
    int i, in, out;

    in = buffer.in;
    out = buffer.out;

    printf("\nSituacao do Buffer:");
    printf("\nin=%d", in);
    printf("\nout=%d", out);

    printf("\nElementos Restantes no Buffer: ");

    while (in != out)
    {
        printf("%d, ", buffer.buffer[out]);
        out = (out + 1) % (buffer.tam);
    }
}

// simula trabalho da thread com tempo "aleatorio"
void trabalha(void)
{
    int i, j, n, m;
    double soma;

    /*
      trecho de codigo que simula o consumo de tempo
      de forma parcialmente aleatoria. Teste retirar
      o codigo do comentario(ativar o codigo).

      srand(time(NULL));
      n = 1000+(rand()%1000);
      m = 5000+(rand()%5000);
      soma = rand();
      for (i=0; i<n; i++)
        {   soma=((soma+(i*2)/2))*(rand()/soma);
            for (j=0; j<m; j++)
                soma=soma-rand()+soma;
        }
    */
}

// codigo da thread produtora
void *produtor(void *ptr)
{
    int *id, dado, sinal;
    id = (int *)ptr;

    srand(time(NULL));

    while (nProd > 0)
    {
        trabalha();

        printf("\nProdutor %d: vai produzir um dado", *id);

        // produz um dado positivo ou negativo aleatoriamente
        dado = rand() % maxNumero;
        sinal = (rand() % 2) * 2 - 1;
        dado = sinal * dado;

        printf("\nProdutor %d: produziu o dado %d", *id, dado);

        pthread_mutex_lock(&nProdMutex);

        if (nProd > 0)
            if (deposita(dado))
            {
                printf("\nProdutor %d: depositou o dado %d", *id, dado);
                nProd--;

                if (nProd == 0)
                    printf("\nProdutor %d: Producoes Finalizadas!!!", *id);
            }
            else
                printf("\nProdutor %d: Nao depositou!", *id);

        pthread_mutex_unlock(&nProdMutex);

        printf("\nProdutor %d: numero de producoes = %d", *id, nProd);
    }
}

// codigo da thread consumidora
void *consumidor(void *ptr)
{
    int *id, i, dado;

    id = (int *)ptr;

    while (nCons > 0)
    {
        trabalha();

        printf("\nConsumidor %d: vai consumir um dado", *id);

        pthread_mutex_lock(&nConsMutex);

        if (nCons > 0)
            if (retira(&dado))
            {
                printf("\nConsumidor %d: consumiu o dado %d", *id, dado);
                nCons--;

                if (nCons == 0)
                    printf("\nConsumidor %d: Consumos Finalizados!!!", *id);
            }
            else
                printf("\nConsumidor %d: Nao consumiu!", *id);

        pthread_mutex_unlock(&nConsMutex);

        printf("\nConsumidor %d: numero de consumos = %d", *id, nCons);
    }
}

// codigo da thread primaria, principal
int main()
{
    pthread_t tProd[maxThread], tCons[maxThread];

    int iretProd[maxThread], iretCons[maxThread],
        tp[maxThread], tc[maxThread], resp,
        i, pindex, cindex, tam;

    sem_init(&freeSpaces, 0, maxBuffer); // Inicializa com o tamanho máximo do buffer
    sem_init(&itensInBuffer, 0, 0);      // Inicializa com zero itens no buffer

    do
    {
        printf("\nProblema do Produtor-Consumidor Multithreaded\n");

        do
        {
            printf("\nQual o tamanho util do buffer? (max = %d) => ", maxBuffer);
            scanf("%d", &(tam));
        } while ((tam < 1) || (tam > maxBuffer));

        criaBuffer(tam);

        do
        {
            printf("\nQuantas threads produtoras? (max=%d) => ", maxThread - 1);
            scanf("%d", &ntp);
        } while ((ntp < 1) || (ntp >= maxThread));

        for (i = 0; i < ntp; i++)
            tp[i] = i;

        do
        {
            printf("\nQuantas threads consumidoras? (max=%d) => ", maxThread - ntp);
            scanf("%d", &ntc);
        } while ((ntc < 1) || (ntp + ntc > maxThread));

        for (i = 0; i < ntc; i++)
            tc[i] = i;

        do
        {
            printf("\nQuantas producoes deseja? => ");
            scanf("%d", &nProd);
        } while (nProd < 1);

        nCons = nProd;

        /* Cria threads produtoras e conumidoras de forma intercalada
           para balancear as atividades de producao e consumo */

        pindex = 0;
        cindex = 0;
        do
        {
            if (pindex < ntp)
            {
                iretProd[pindex] = pthread_create(&tProd[pindex], NULL, produtor, (void *)&tp[pindex]);
                pindex++;
            }

            if (cindex < ntc)
            {
                iretCons[cindex] = pthread_create(&tCons[cindex], NULL, consumidor, (void *)&tc[cindex]);
                cindex++;
            }
        } while ((pindex < ntp) || (cindex < ntc));

        trabalha();

        // espera todas as threads acabarem

        for (pindex = 0; pindex < ntp; pindex++)
            pthread_join(tProd[pindex], NULL);
        for (cindex = 0; cindex < ntc; cindex++)
            pthread_join(tCons[cindex], NULL);

        mostraBuffer();

        printf("\nDeseja Nova Execucao, <1>Sim <2>Nao? => ");
        scanf("%d", &resp);

    } while (resp == 1);

    return 0;
}
