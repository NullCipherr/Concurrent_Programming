// Aluno e RA
// Andrei Roberto da Costa 107975

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Exercicio 8 - Busca x em um vetor de n elementos com k threads

#define maxElem 100
#define NUM_THREADS 4

typedef struct
{
    int id;
    int *array; // Array.
    int start;  // Início.
    int end;    // Fim.
    int x;      // Número a ser buscado.
    int result; // Resultado.
} thread_data;

typedef int tipoVetor[maxElem]; // Vetor de inteiros.
tipoVetor vetorA, vetorAux;     // Vetores: A e Auxiliar.
int tam;                        // Tamnho do vetor.

// Gera um vetor de inteiros aleatórios.
void geraVetor(tipoVetor V, int tam)
{
    int i;

    for (i = 0; i < tam; i++)
    {
        V[i] = rand() % 100;
    }
}

// Mostra um vetor de inteiros.
void mostraVetor(char *ident, tipoVetor V, int tam)
{
    int i;

    printf("\nVetor %s: ", ident);
    for (i = 0; i < tam; i++)
    {
        printf("%d ", V[i]);
    }
    printf("\n");
}

// Copia um vetor de inteiros.
void copiaVetor(tipoVetor V1, int ini, int fim, tipoVetor V2)
{
    int i;

    for (i = ini; i <= fim; i++)
    {
        V2[i] = V1[i];
    }
}

// Ordena um vetor de inteiros.
void *ordenaSelecao(void *ptr)
{
    thread_data *data = (thread_data *)ptr;
    int id = data->id;
    int posIns, posAfrente, posPraTras, posMenor, posMaior, aux;

    if (id == 1)
    {
        for (posIns = 0; posIns < tam / 2; posIns++)
        {
            posMenor = posIns;
            for (posAfrente = posIns + 1; posAfrente < tam; posAfrente++)
            {
                if (vetorA[posMenor] > vetorA[posAfrente])
                    posMenor = posAfrente;
            }
            aux = vetorA[posIns];
            vetorA[posIns] = vetorA[posMenor];
            vetorA[posMenor] = aux;
        }
    }
    else
    {
        for (posIns = tam - 1; posIns >= tam / 2; posIns--)
        {
            posMaior = posIns;
            for (posPraTras = posIns - 1; posPraTras > 0; posPraTras--)
            {
                if (vetorAux[posMaior] < vetorAux[posPraTras])
                    posMaior = posPraTras;
            }
            aux = vetorAux[posIns];
            vetorAux[posIns] = vetorAux[posMaior];
            vetorAux[posMaior] = aux;
        }
    }
}

void *buscaBinariaBalanceada(void *arg)
{
    thread_data *data = (thread_data *)arg;
    int start = data->start; // Início.
    int left = data->start;  // Esquerda.
    int right = data->end;   // Direita.
    int result = -1;         // Resultado.

    // Enquanto houver elementos a serem verificados.
    while (left <= right)
    {
        int mid = left + (right - left) / 2; // Meio, sendo o início + (fim - início) / 2. = 0 + (30 - 0) / 2 = 15. (para o array de 30 elementos).

        // Se o elemento do meio for igual ao número a ser buscado, retorna o índice.
        if (data->array[mid] == data->x)
        {
            data->result = mid;
            pthread_exit(NULL);
        }
        // Se o elemento do meio for menor que o número a ser buscado, a busca é realizada a direita.
        else if (data->array[mid] < data->x)
        {
            left = mid + 1; // Esquerda = meio + 1.
        }
        // Se o elemento do meio for maior que o número a ser buscado, a busca é realizada a esquerda.
        else
        {
            right = mid - 1; // Direita = meio - 1.
        }
    }

    pthread_exit(NULL);
}

// Função principal.
void main(void)
{
    pthread_t thread[NUM_THREADS]; // Threads.
    thread_data data[NUM_THREADS]; // Dados das threads.
    int iret[NUM_THREADS];         // Retornos das threads.

    srand(time(NULL)); // Inicializa o gerador de números aleatórios.

    printf("\nDigite o tamanho do vetor => "); // Solicita o tamanho do vetor.
    scanf("%d", &tam);                         // Lê o tamanho do vetor.

    geraVetor(vetorA, tam);               // Gera o vetor A.
    mostraVetor("Original", vetorA, tam); // Mostra o vetor A.

    copiaVetor(vetorA, 0, tam - 1, vetorAux); // Copia o vetor A para o vetor Auxiliar.
    mostraVetor("Copia", vetorAux, tam);      // Mostra o vetor Auxiliar.

    int range = tam / NUM_THREADS; // Tamanho da parte do vetor que cada thread irá processar.

    for (int i = 0; i < NUM_THREADS; i++)
    {
        data[i].id = i + 1;
        pthread_create(&thread[i], NULL, ordenaSelecao, &data[i]); // Cria a thread 1
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(thread[i], NULL); // Aguarda a thread 1 terminar.
    }

    mostraVetor("A Ordenado Parcialmente", vetorA, tam);     // Mostra o vetor A ordenado parcialmente.
    mostraVetor("Aux Ordenado Parcialmente", vetorAux, tam); // Mostra o vetor Auxiliar ordenado parcialmente.

    copiaVetor(vetorAux, tam / 2, tam - 1, vetorA); // Copia o vetor Auxiliar para o vetor A.

    mostraVetor("Ordenado", vetorA, tam); // Mostra o vetor A ordenado.

    // Exercicio 15 - Busca x em um vetor de n elementos com k threads
    printf("\n");
    printf("Digite o número a ser buscado:"); // Solicita o número a ser buscado.
    int x;                                    // Declaração do número a ser buscado.
    scanf("%d", &x);                          // Número a ser buscado.

    for (int i = 0; i < NUM_THREADS; i++)
    {
        data[i].id = i + 1;                                                 // ID.
        data[i].array = vetorA;                                             // Array.
        data[i].start = i * range;                                          // Início.
        data[i].end = (i == NUM_THREADS - 1) ? tam : (i + 1) * range;       // Fim.
        data[i].x = x;                                                      // Número a ser buscado.
        data[i].result = -1;                                                // Resultado.
        pthread_create(&thread[i], NULL, buscaBinariaBalanceada, &data[i]); // Cria a thread.
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(thread[i], NULL);
        if (data[i].result != -1)
        {
            printf("\nNúmero encontrado na posição %d\n", data[i].result);
        }
    }
}