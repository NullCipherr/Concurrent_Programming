// Aluno e RA
// Andrei Roberto da Costa RA107975
// Kananda Caroline RA116382

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX 100

typedef struct {
    int elementos[MAX][MAX];
    int linhas;
    int colunas;
} matriz_data;

matriz_data A, B, C;

typedef struct {
    matriz_data *A;
    matriz_data *B;
    matriz_data *C;
    int linha;
    int coluna;
} thread_data_t;

void *produtoEscalar(void *param) 
{
    thread_data_t *data = (thread_data_t *)param;
    int soma = 0;
    
    for (int i = 0; i < data->A->colunas; i++) 
    {
        // printf("Multiplicação de %d e %d: %d \n", data->A->elementos[data->linha][i], data->B->elementos[i][data->coluna], (data->A->elementos[data->linha][i] * data->B->elementos[i][data->coluna])) ;
        soma += data->A->elementos[data->linha][i] * data->B->elementos[i][data->coluna];
        // printf("Soma é igual a %d \n", soma) ;
    }
    data->C->elementos[data->linha][data->coluna] = soma;
    free(param);
    pthread_exit(0);
}

void geraMatriz(matriz_data *M) 
{
    for (int i = 0; i < M->linhas; i++) 
    {
        for (int j = 0; j < M->colunas; j++) 
        {
            M->elementos[i][j] = rand() % 10;
        }
    }
}

void mostraMatriz(matriz_data *M) 
{
    for (int i = 0; i < M->linhas; i++) 
    {
        for (int j = 0; j < M->colunas; j++) 
        {
            printf("%d ", M->elementos[i][j]);
        }
        printf("\n");
    }
}

int main() 
{
    int thread_count = 0;
    pthread_t threads[MAX * MAX];

    srand(time(NULL));

    // Entrada de dimensões das matrizes
    printf("Digite as dimensoes da matriz A (m ESPAÇO n): ");
    scanf("%d %d", &A.linhas, &A.colunas);
    printf("Digite o numero de colunas da matriz B (p): ");
    scanf("%d", &B.colunas);

    B.linhas = A.colunas;
    C.linhas = A.linhas;
    C.colunas = B.colunas;

    // Geração das matrizes
    geraMatriz(&A);
    geraMatriz(&B);

    // Exibindo as matrizes A e B
    printf("\nMatriz A:\n");
    mostraMatriz(&A);
    printf("\nMatriz B:\n");
    mostraMatriz(&B);

    // Criando as threads para calcular C = A * B
    for (int i = 0; i < A.linhas; i++) 
    {
        for (int j = 0; j < B.colunas; j++) 
        {
            thread_data_t *data = (thread_data_t *)malloc(sizeof(thread_data_t));
            data->A = &A;
            data->B = &B;
            data->C = &C;
            data->linha = i;
            data->coluna = j;
            pthread_create(&threads[thread_count], NULL, produtoEscalar, (void *)data);
            thread_count++;
        }
    }

    // Esperando todas as threads terminarem
    for (int i = 0; i < thread_count; i++) 
    {
        pthread_join(threads[i], NULL);
    }

    // Exibindo a matriz C
    printf("\nMatriz C (resultado):\n");
    mostraMatriz(&C);

    return 0;
}

