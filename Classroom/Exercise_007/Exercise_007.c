// Alunos e RA
// Andrei Roberto da Costa - 107975
// Kananda Caroline Vieira da Silva - 116382

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// Estrutura para armazenar os dados que serão passados para as threads
typedef struct
{
    int *arr;
    int inicio;
    int fim;
} Dados_T;

// Função para ordenar a metade do vetor em ordem crescente
void *ordenacao_selecao(void *args)
{
    Dados_T *dados = (Dados_T *)args;
    int *arr = dados->arr;
    int inicio = dados->inicio;
    int fim = dados->fim;

    for (int i = inicio; i < fim; i++)
    {
        int indice_min = i;
        for (int j = i + 1; j < fim; j++)
        {
            if (arr[j] < arr[indice_min])
            {
                indice_min = j;
            }
        }
        // Troca o elemento mínimo com o início da sublista
        int temp = arr[i];
        arr[i] = arr[indice_min];
        arr[indice_min] = temp;
    }
    pthread_exit(NULL);
}

// Função para mesclar as duas metades ordenadas
void mesclar(int *arr, int inicio, int meio, int fim)
{
    int i, j, k;
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    // Cria arrays temporários
    int *esquerda = (int *)malloc(n1 * sizeof(int));
    int *direita = (int *)malloc(n2 * sizeof(int));

    // Copia os dados para os arrays temporários
    for (i = 0; i < n1; i++)
        esquerda[i] = arr[inicio + i];
    for (j = 0; j < n2; j++)
        direita[j] = arr[meio + 1 + j];

    // Mescla os arrays temporários de volta ao array original
    i = 0;
    j = 0;
    k = inicio;
    while (i < n1 && j < n2)
    {
        if (esquerda[i] <= direita[j])
        {
            arr[k] = esquerda[i];
            i++;
        }
        else
        {
            arr[k] = direita[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes do array esquerda, caso exista.
    while (i < n1)
    {
        arr[k] = esquerda[i];
        i++;
        k++;
    }

    // Copia os elementos restantes do array direita, caso exista.
    while (j < n2)
    {
        arr[k] = direita[j];
        j++;
        k++;
    }

    // Libera a memória alocada
    free(esquerda);
    free(direita);
}

int main()
{
    // Variável para armazenar o número de elementos do vetor
    int numero_elementos;

    // Realiza a leitura do número de elementos do vetor
    printf("Tamanho do vetor (n): ");
    scanf("%d", &numero_elementos);
    printf("\n");

    // Cria o vetor com n elementos
    int vetor[numero_elementos];

    printf("Digite os elementos do vetor: \n");
    for (int i = 0; i < numero_elementos; i++)
    {
        printf("Elemento %d: ", i + 1);
        scanf("%d", &vetor[i]);
    }

    pthread_t thread1, thread2;
    Dados_T dados1 = {vetor, 0, numero_elementos / 2};
    Dados_T dados2 = {vetor, numero_elementos / 2, numero_elementos};

    // Cria as threads para ordenar as metades
    pthread_create(&thread1, NULL, ordenacao_selecao, (void *)&dados1);
    pthread_create(&thread2, NULL, ordenacao_selecao, (void *)&dados2);

    // Espera as threads finalizarem
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Mescla as duas metades ordenadas
    mesclar(vetor, 0, numero_elementos / 2 - 1, numero_elementos - 1);

    // Exibe o vetor ordenado
    printf("\nVetor ordenado: ");
    for (int i = 0; i < numero_elementos; i++)
    {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    return 0;
}