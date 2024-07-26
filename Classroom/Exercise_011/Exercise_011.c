/*
    Resolução do desafio do Exemplo 14
    Aluno: Andrei Roberto da Costa      RA: 107975
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define maxBuffer 10000 // tamanho maximo do buffer
#define maxNumero 10000 // valor maximo do numero produzido
#define maxThread 300   // numero maximo de threads

/*
    Estrutura do buffer circular
    buffer: local de armazenamento circular
    in: posicao de insercao
    out: posicao de retirada
    count: quantidade de elementos no buffer
    tam: tamanho util do buffer
*/
typedef struct
{
    int buffer[maxBuffer]; // local de armazenamento circular
    int in,                // posicao de insercao
        out,               // posicao de retirada
        count,             // quantidade de elementos no buffer
        tam;               // tamanho util do buffer
} tBuffer;

// buffer circular
tBuffer buffer;

// variaveis globais
int nProd, // quantidade de dados a serem fabricados (producoes)
    nCons, // quantidade de dados a serem consumidos (consumos),
           // que nesta implementacao e igual ao numero de producoes
    ntp,   // numero de threads produtoras
    ntc;   // numero de threads consumidoras

// mutexes
pthread_mutex_t buffer_mutex = PTHREAD_MUTEX_INITIALIZER; // mutex do buffer
pthread_mutex_t prod_mutex = PTHREAD_MUTEX_INITIALIZER;   // mutex dos produtores
pthread_mutex_t cons_mutex = PTHREAD_MUTEX_INITIALIZER;   // mutex dos consumidores

// inicializa a estrutura do buffer
void criaBuffer(int tam)
{
    buffer.in = -1;   // posicao de insercao
    buffer.out = -1;  // posicao de retirada
    buffer.count = 0; // quantidade de elementos no buffer
    buffer.tam = tam; // tamanho util do buffer
}

/*
    deposita um dado no buffer
    dado: dado a ser depositado
    retorna 1 se conseguiu depositar, 0 caso contrario
*/
int deposita(int dado)
{
    pthread_mutex_lock(&buffer_mutex); // trava o buffer

    // se o buffer nao estiver cheio insere o dado, caso contrario retorna sem fazer nada
    if (buffer.count != buffer.tam)
    {
        buffer.in = (buffer.in + 1) % (buffer.tam); // calcula a nova posicao de insercao
        buffer.buffer[buffer.in] = dado;            // deposita o dado
        buffer.count++;                             // incrementa a quantidade de elementos no buffer
        pthread_mutex_unlock(&buffer_mutex);        // destrava o buffer
        return (1);                                 // retorna sucesso
    }
    else
    {
        pthread_mutex_unlock(&buffer_mutex); // destrava o buffer
        return (0);                          // retorna falha
    }
}

/*
    retira um dado do buffer
    dado: endereco onde sera depositado o dado retirado
    retorna 1 se conseguiu retirar, 0 caso contrario
*/
int retira(int *dado)
{
    pthread_mutex_lock(&buffer_mutex); // trava o buffer

    // se o buffer nao estiver vazio retira o dado, caso contrario retorna sem fazer nada
    if (buffer.count != 0)
    {
        buffer.out = (buffer.out + 1) % (buffer.tam); // calcula a nova posicao de retirada
        *dado = buffer.buffer[buffer.out];            // retira o dado
        buffer.count--;                               // decrementa a quantidade de elementos no buffer
        pthread_mutex_unlock(&buffer_mutex);          // destrava o buffer
        return (1);                                   // retorna sucesso
    }
    else
    {
        pthread_mutex_unlock(&buffer_mutex); // destrava o buffer
        return (0);                          // retorna falha
    }
}

/*
    mostra o conteudo do buffer
*/
void mostraBuffer(void)
{
    int i, in, out; // indices de insercao e retirada

    pthread_mutex_lock(&buffer_mutex); // trava o buffer
    in = buffer.in;                    // copia os indices de insercao e retirada
    out = buffer.out;                  // para variaveis locais

    printf("\nSituacao do Buffer:");
    printf("\nin=%d", in);
    printf("\nout=%d", out);

    printf("\nElementos Restantes no Buffer: ");

    // mostra os elementos do buffer
    while (in != out)
    {
        printf("%d, ", buffer.buffer[out]);
        out = (out + 1) % (buffer.tam);
    }

    pthread_mutex_unlock(&buffer_mutex); // destrava o buffer
}

/*
    funcao que simula um trabalho qualquer
*/
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

    while (1)
    {
        trabalha();

        printf("\nProdutor %d: vai produzir um dado", *id);

        // Produz um dado positivo ou negativo aleatoriamente
        dado = rand() % maxNumero;
        sinal = (rand() % 2) * 2 - 1;
        dado = sinal * dado;

        printf("\nProdutor %d: produziu o dado %d", *id, dado);

        pthread_mutex_lock(&prod_mutex); // trava o mutex dos produtores
        if (nProd > 0)
        {
            if (deposita(dado))
            {
                printf("\nProdutor %d: depositou o dado %d", *id, dado);
                nProd--;

                if (nProd == 0)
                    printf("\nProdutor %d: Producoes Finalizadas!!!", *id);
            }
            else
                printf("\nProdutor %d: Nao depositou!", *id);

            printf("\nProdutor %d: numero de producoes = %d", *id, nProd);
        }
        pthread_mutex_unlock(&prod_mutex); // destrava o mutex dos produtores

        if (nProd == 0)
            break;
    }

    return NULL;
}

// codigo da thread consumidora
void *consumidor(void *ptr)
{
    int *id, i, dado;

    id = (int *)ptr;

    while (1)
    {
        trabalha();

        printf("\nConsumidor %d: vai consumir um dado", *id);

        pthread_mutex_lock(&cons_mutex); // trava o mutex dos consumidores
        if (nCons > 0)
        {
            if (retira(&dado))
            {
                printf("\nConsumidor %d: consumiu o dado %d", *id, dado);
                nCons--;

                if (nCons == 0)
                    printf("\nConsumidor %d: Consumos Finalizados!!!", *id);
            }
            else
                printf("\nConsumidor %d: Nao consumiu!", *id);

            printf("\nConsumidor %d: numero de consumos = %d", *id, nCons);
        }
        pthread_mutex_unlock(&cons_mutex); // destrava o mutex dos consumidores

        if (nCons == 0)
            break;
    }

    return NULL;
}

// codigo da thread primaria, principal
int main()
{
    // variaveis locais
    pthread_t tProd[maxThread], tCons[maxThread];
    int iretProd[maxThread], iretCons[maxThread],
        tp[maxThread], tc[maxThread], resp,
        i, pindex, cindex, tam;

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