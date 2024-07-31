// 1. Mutexes e Filas(Queue)
//
// Mutexes são utilizados com filas para garantir que apenas uma thread possa acessar a fila por vez.
// Além disso, mutexes são utilizados para garantir que a fila não seja acessada por uma thread enquanto outra thread está modificando a fila.
//
// 2. Exercicio
//
// Implemente uma fila(queue) segura para threads utilizando mutaxes para sincronizar o acesso ás operações de enfileirar(enqueue) e desenfileirar(dequeue) elementos.
// A fila deve ser implementada utilizando uma lista ligada simples, onde cada nó contém um inteiro.
// A fila deve possuir as seguintes operações:
// - enqueue: insere um elemento na fila
// - dequeue: remove um elemento da fila
// - print: imprime os elementos da fila

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Estrutura do nó
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// Estrutura da fila
typedef struct Queue
{
    Node *head;
    Node *tail;
    pthread_mutex_t queue_mutex;
} Queue;

/*
 * Função que inicializa a fila
 * @param queue: fila
 * @return void
 */
void init_queue(Queue *queue)
{
    queue->head = NULL;
    queue->tail = NULL;
    pthread_mutex_init(&queue->queue_mutex, NULL);
}

/*
 * Função que insere um elemento na fila
 * @param queue: fila
 * @param data: dado a ser inserido
 * @return void
 */
void enqueue(Queue *queue, int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;

    // Bloqueia o mutex
    pthread_mutex_lock(&queue->queue_mutex);

    // Se a fila estiver vazia, insere o elemento no início
    if (queue->head == NULL)
    {
        printf("Inserindo no inicio da fila : %d\n", data);
        queue->head = new_node;
        queue->tail = new_node;
    }
    else // Insere o elemento no final da fila
    {
        printf("Inserindo no final da fila:  %d\n", data);
        queue->tail->next = new_node;
        queue->tail = new_node;
    }

    // Desbloqueia o mutex
    pthread_mutex_unlock(&queue->queue_mutex);
}

/*
 * Função que remove um elemento da fila
 * @param queue: fila
 * @return int: dado removido
 */
int dequeue(Queue *queue)
{
    // Bloqueia o mutex
    pthread_mutex_lock(&queue->queue_mutex);

    // Verifica se a fila está vazia
    if (queue->head == NULL)
    {
        // Desbloqueia o mutex
        pthread_mutex_unlock(&queue->queue_mutex);
        return -1;
    }

    Node *node = queue->head; // Salva o nó a ser removido
    int data = node->data;    // Salva o dado do nó removido

    printf("Removendo do inicio da fila: %d\n", data);

    queue->head = queue->head->next; // Atualiza o início da fila

    free(node); // Libera a memória do nó removido

    // Desbloqueia o mutex
    pthread_mutex_unlock(&queue->queue_mutex);

    return data; // Retorna o dado removido
}

/*
 * Função que imprime os elementos da fila
 * @param queue: fila
 * @return void
 */
void print(Queue *queue)
{
    // Bloqueia o mutex
    pthread_mutex_lock(&queue->queue_mutex);

    Node *current = queue->head; // Inicia a partir do início da fila

    // Percorre a fila e imprime os elementos
    while (current != NULL)
    {
        printf("%d ", current->data); // Imprime o elemento
        current = current->next;      // Avança para o próximo elemento
    }

    printf("\n");

    // Desbloqueia o mutex
    pthread_mutex_unlock(&queue->queue_mutex);
}

int main()
{
    Queue queue;        // Fila
    init_queue(&queue); // Inicializa a fila

    enqueue(&queue, 1); // Insere o elemento 1 na fila
    enqueue(&queue, 2); // Insere o elemento 2 na fila
    enqueue(&queue, 3); // Insere o elemento 3 na fila

    print(&queue); // Imprime os elementos da fila

    dequeue(&queue); // Remove um elemento da fila

    print(&queue); // Imprime os elementos da fila

    return 0; // Finaliza o programa
}