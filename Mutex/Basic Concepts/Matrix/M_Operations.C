#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex; // Mutex

struct Matriz
{
    int rows;
    int cols;
    int **matriz1;
    int **matriz2;
    int **result;
};

struct ThreadArgs
{
    struct Matriz *matriz;
    int row;
};

void *sumMatriz(void *arg)
{
    struct ThreadArgs *args = (struct ThreadArgs *)arg;
    struct Matriz *matriz = args->matriz;
    int row = args->row;

    pthread_mutex_lock(&mutex); // Bloqueia o mutex
    printf("\nThread %d - Soma dos elementos da linha %d\n", row + 1, row + 1);
    for (int i = 0; i < matriz->cols; i++)
    {
        printf("Elemento %d da linha %d: %d + %d\n", i + 1, row + 1, matriz->matriz1[row][i], matriz->matriz2[row][i]);
        matriz->result[row][i] = matriz->matriz1[row][i] + matriz->matriz2[row][i]; // Soma os elementos das matrizes
    }
    pthread_mutex_unlock(&mutex); // Libera o mutex
    pthread_exit(NULL);
}

void *multMatriz(void *arg)
{
    struct ThreadArgs *args = (struct ThreadArgs *)arg;
    struct Matriz *matriz = args->matriz;
    int row = args->row;

    pthread_mutex_lock(&mutex); // Bloqueia o mutex
    printf("\nThread %d - Multiplicação dos elementos da linha %d\n", row + 1, row + 1);
    for (int i = 0; i < matriz->cols; i++)
    {
        printf("Elemento %d da linha %d: %d * %d\n", i + 1, row + 1, matriz->matriz1[row][i], matriz->matriz2[row][i]);
        matriz->result[row][i] = matriz->matriz1[row][i] * matriz->matriz2[row][i]; // Multiplica os elementos das matrizes
    }
    pthread_mutex_unlock(&mutex); // Libera o mutex
    pthread_exit(NULL);
}

void *transposeMatriz(void *arg)
{
    struct ThreadArgs *args = (struct ThreadArgs *)arg;
    struct Matriz *matriz = args->matriz;
    int row = args->row;

    pthread_mutex_lock(&mutex); // Bloqueia o mutex
    printf("\nThread %d - Transposição dos elementos da linha %d\n", row + 1, row + 1);
    for (int i = 0; i < matriz->cols; i++)
    {
        printf("Elemento %d da linha %d: %d\n", i + 1, row + 1, matriz->matriz1[row][i]);
        matriz->result[i][row] = matriz->matriz1[row][i]; // Transpõe os elementos da matriz
    }
    pthread_mutex_unlock(&mutex); // Libera o mutex
    pthread_exit(NULL);
}

void *gerarMatriz(void *arg)
{
    struct ThreadArgs *args = (struct ThreadArgs *)arg;
    struct Matriz *matriz = args->matriz;
    int row = args->row;

    pthread_mutex_lock(&mutex);
    printf("\nThread %d - Gerando matriz %d\n", row + 1, row + 1);
    for (int i = 0; i < matriz->cols; i++)
    {
        matriz->matriz1[row][i] = rand() % 20; // Gera um número aleatório entre 0 e 19
        matriz->matriz2[row][i] = rand() % 20; // Gera um número aleatório entre 0 e 19
        printf("Elemento %d da linha %d da matriz 1: %d\n", i + 1, row + 1, matriz->matriz1[row][i]);
        printf("Elemento %d da linha %d da matriz 2: %d\n", i + 1, row + 1, matriz->matriz2[row][i]);
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void printMatriz(struct Matriz *matriz)
{
    printf("\nMatriz 1:\n");
    for (int i = 0; i < matriz->rows; i++)
    {
        for (int j = 0; j < matriz->cols; j++)
        {
            printf("%d ", matriz->matriz1[i][j]); // Imprime a matriz 1
        }
        printf("\n");
    }

    printf("\nMatriz 2:\n");
    for (int i = 0; i < matriz->rows; i++)
    {
        for (int j = 0; j < matriz->cols; j++)
        {
            printf("%d ", matriz->matriz2[i][j]); // Imprime a matriz 2
        }
        printf("\n");
    }
}

void printMatrizResultante(struct Matriz *matriz)
{
    printf("\nMatriz resultante:\n");
    for (int i = 0; i < matriz->rows; i++)
    {
        for (int j = 0; j < matriz->cols; j++)
        {
            printf("%d ", matriz->result[i][j]); // Imprime a matriz resultante
        }
        printf("\n");
    }
}

void menu(struct Matriz *matriz)
{
    int opcao;
    printf("\nManipulação de matrizes com Threads\n");
    printf("====================================\n");
    printf("        1 - Gerar matrizes\n");
    printf("        2 - Mostrar matrizes\n");
    printf("        3 - Soma\n");
    printf("        4 - Multiplicação\n");
    printf("        5 - Transposição\n");
    printf("        0 - Sair\n");
    printf("====================================\n");
    printf("Opção: ");
    scanf("%d", &opcao);

    if (opcao == 0)
    {
        exit(0);
    }

    if (opcao == 2)
    {
        printMatriz(matriz); // Imprime as matrizes
        return;
    }

    pthread_t threads[matriz->rows];             // Vetor de threads, no nosso caso, 3 threads.
    struct ThreadArgs thread_args[matriz->rows]; // Vetor de argumentos, no nosso caso, 3 argumentos.

    pthread_mutex_init(&mutex, NULL); // Inicializa o mutex

    for (int i = 0; i < matriz->rows; i++)
    {
        printf("Criando thread %d\n", i + 1);
        thread_args[i].matriz = matriz;
        thread_args[i].row = i;
        if (opcao == 1)
        {
            pthread_create(&threads[i], NULL, gerarMatriz, &thread_args[i]); // Cria as threads
        }
        else if (opcao == 3)
        {
            pthread_create(&threads[i], NULL, sumMatriz, &thread_args[i]); // Cria as threads
        }
        else if (opcao == 4)
        {
            pthread_create(&threads[i], NULL, multMatriz, &thread_args[i]); // Cria as threads
        }
        else if (opcao == 5)
        {
            pthread_create(&threads[i], NULL, transposeMatriz, &thread_args[i]); // Cria as threads
        }
    }

    for (int i = 0; i < matriz->rows; i++)
    {
        pthread_join(threads[i], NULL); // Aguarda a finalização das threads
    }

    pthread_mutex_destroy(&mutex); // Destrói o mutex

    if (opcao == 3 || opcao == 4 || opcao == 5)
    {
        printMatrizResultante(matriz); // Imprime a matriz resultante
    }
}

int main()
{
    struct Matriz matriz;

    printf("Digite o número de linhas da matriz: ");
    scanf("%d", &matriz.rows);
    printf("Digite o número de colunas da matriz: ");
    scanf("%d", &matriz.cols);

    matriz.matriz1 = (int **)malloc(matriz.rows * sizeof(int *));
    matriz.matriz2 = (int **)malloc(matriz.rows * sizeof(int *));
    matriz.result = (int **)malloc(matriz.rows * sizeof(int *));

    for (int i = 0; i < matriz.rows; i++)
    {
        matriz.matriz1[i] = (int *)malloc(matriz.cols * sizeof(int));
        matriz.matriz2[i] = (int *)malloc(matriz.cols * sizeof(int));
        matriz.result[i] = (int *)malloc(matriz.cols * sizeof(int));
    }

    while (1)
    {
        menu(&matriz); // Chama o menu
    }

    // Libera a memória alocada
    for (int i = 0; i < matriz.rows; i++)
    {
        free(matriz.matriz1[i]);
        free(matriz.matriz2[i]);
        free(matriz.result[i]);
    }
    free(matriz.matriz1);
    free(matriz.matriz2);
    free(matriz.result);

    return 0;
}