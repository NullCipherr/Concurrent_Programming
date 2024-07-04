#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

// Definição de número máximo de elementos nas matrizes
#define MAX 100

// Estrutura de dados para armazenar uma matriz
typedef struct
{
    int elementos[MAX][MAX]; // Matriz de elementos
    int linhas;              // Número de linhas
    int colunas;             // Número de colunas
} matriz_data;

// Matrizes A, B e C
matriz_data A, B, C;

// Estrutura de dados para passar parâmetros para as threads
typedef struct
{
    matriz_data *A; // Ponteiro para a matriz A
    matriz_data *B; // Ponteiro para a matriz B
    matriz_data *C; // Ponteiro para a matriz C
    int linha;      // Índice da linha
    int coluna;     // Índice da coluna
} thread_data_t;

/**
 * Função que calcula o produto escalar de uma linha da matriz A com uma coluna da matriz B
 * e armazena o resultado na matriz C.
 * @param param Ponteiro para a estrutura de dados com os parâmetros da thread
 * @return void* Ponteiro para o resultado da thread
 */
void *produtoEscalar(void *param)
{
    thread_data_t *data = (thread_data_t *)param; // Convertendo o ponteiro para o tipo correto
    int soma = 0;                                 // Variável para armazenar o resultado do produto escalar

    // Calculando o produto escalar
    for (int i = 0; i < data->A->colunas; i++)
    {
        // printf("Multiplicação de %d e %d: %d \n", data->A->elementos[data->linha][i], data->B->elementos[i][data->coluna], (data->A->elementos[data->linha][i] * data->B->elementos[i][data->coluna])) ;

        soma += data->A->elementos[data->linha][i] * data->B->elementos[i][data->coluna]; // Multiplicação dos elementos, somando o resultado.

        // printf("Soma é igual a %d \n", soma) ;
    }
    data->C->elementos[data->linha][data->coluna] = soma; // Armazenando o resultado na matriz C
    free(param);                                          // Liberando a memória alocada para a estrutura de dados
    pthread_exit(0);                                      // Terminando a thread
}

// Função para gerar uma matriz com valores aleatórios
void geraMatriz(matriz_data *M)
{
    for (int i = 0; i < M->linhas; i++)
    {
        for (int j = 0; j < M->colunas; j++)
        {
            M->elementos[i][j] = rand() % 10; // Gera um número aleatório entre 0 e 9
        }
    }
}

// Função para exibir uma matriz
void mostraMatriz(matriz_data *M)
{
    for (int i = 0; i < M->linhas; i++)
    {
        for (int j = 0; j < M->colunas; j++)
        {
            printf("%d ", M->elementos[i][j]); // Exibe o elemento
        }
        printf("\n");
    }
}

// Função principal
int main()
{
    // Variáveis
    int thread_count = 0;         // Contador de threads
    pthread_t threads[MAX * MAX]; // Vetor de threads

    srand(time(NULL));

    // Entrada de dimensões das matrizes
    printf("Digite as dimensoes da matriz A (m ESPAÇO n): "); // m linhas e n colunas
    scanf("%d %d", &A.linhas, &A.colunas);                    // Recebe as dimensões da matriz A
    printf("Digite o numero de colunas da matriz B (p): ");   // p colunas
    scanf("%d", &B.colunas);                                  // Recebe o número de colunas da matriz B

    B.linhas = A.colunas;  // O número de linhas da matriz B é igual ao número de colunas da matriz A
    C.linhas = A.linhas;   // O número de linhas da matriz C é igual ao número de linhas da matriz A
    C.colunas = B.colunas; // O número de colunas da matriz C é igual ao número de colunas da matriz B

    // Geração das matrizes
    geraMatriz(&A); // Gera a matriz A
    geraMatriz(&B); // Gera a matriz B

    // Exibindo as matrizes A e B
    printf("\nMatriz A:\n");
    mostraMatriz(&A);
    printf("\nMatriz B:\n");
    mostraMatriz(&B);

    // Criando as threads
    // As threads irão calcular C = A * B
    // A matriz A é uma matriz de dimensões m x n
    // A matriz B é uma matriz de dimensões n x p
    // A matriz C é uma matriz de dimensões m x p
    // As threads irão dividir o trabalho de calcular C
    for (int i = 0; i < A.linhas; i++)
    {
        for (int j = 0; j < B.colunas; j++)
        {
            thread_data_t *data = (thread_data_t *)malloc(sizeof(thread_data_t));       // Alocando memória para a estrutura de dados
            data->A = &A;                                                               // Passando os ponteiros para as matrizes A, B e C
            data->B = &B;                                                               // Passando os ponteiros para as matrizes A, B e C
            data->C = &C;                                                               // Passando os ponteiros para as matrizes A, B e C
            data->linha = i;                                                            // Passando o índice da linha
            data->coluna = j;                                                           // Passando o índice da coluna
            pthread_create(&threads[thread_count], NULL, produtoEscalar, (void *)data); // Criando a thread
            thread_count++;                                                             // Incrementando o contador de threads
        }
    }

    // Aguardando o término das threads
    for (int i = 0; i < thread_count; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Exibindo a matriz C
    printf("\nMatriz C (resultado):\n");
    mostraMatriz(&C);

    // Exibindo o número de threads criadas
    printf("Número de threads criadas: %d\n", thread_count);

    // Finalizando o programa
    return 0;
}
