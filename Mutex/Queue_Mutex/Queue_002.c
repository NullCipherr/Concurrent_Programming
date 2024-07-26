// 1. Mutexes e Filas(Queue)
//
// 2. Exercicio
//
// Implemente uma fila(queue) segura para threads utilizando mutaxes para sincronizar o acesso ás operações de enfileirar(enqueue) e desenfileirar(dequeue) elementos.
// A fila deve ser implementada utilizando uma lista ligada simples, onde cada nó contém um inteiro.
// A fila deve possuir as seguintes operações:
// - createQueue: cria uma fila
// - enqueue: insere um elemento na fila
// - dequeue: remove um elemento da fila
// - destroyQueue: destroi a fila
// - enqueue_thread: função que enfileira elementos na fila
// - dequeue_thread: função que desenfileira elementos da fila
// - print: imprime os elementos da fila

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Estrutura do nó
typedef struct Node
{
    int data;          // Dado
    struct Node *next; // Próximo nó
} Node;

// Estrutura da fila
typedef struct Queue
{
    Node *head;                  // Início da fila
    Node *tail;                  // Final da fila
    pthread_mutex_t queue_mutex; //
} Queue;

/*
 * Função que cria uma fila
 * @return fila
 */
Queue *createQueue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue)); // Aloca memória para a fila
    queue->head = NULL;                            // Início da fila é NULL
    queue->tail = NULL;                            // Final da fila é NULL
    pthread_mutex_init(&queue->queue_mutex, NULL); // Inicializa o mutex
    return queue;                                  // Retorna a fila
}

/*
 * Função que insere um elemento na fila
 * @param queue: fila
 * @param data: dado a ser inserido
 * @return void
 */
void enqueue(Queue *queue, int data)
{
    // Bloqueia o mutex
    pthread_mutex_lock(&queue->queue_mutex);

    Node *new_node = (Node *)malloc(sizeof(Node)); // Aloca memória para o novo nó
    new_node->data = data;                         // Atribui o dado ao novo nó
    new_node->next = NULL;                         // O próximo nó é NULL

    // Se a fila estiver vazia, insere o elemento no início
    if (queue->head == NULL)
    {
        queue->head = new_node; // O início da fila é o novo nó
        queue->tail = new_node; // O final da fila é o novo nó
    }
    else // Insere o elemento no final da fila
    {
        queue->tail->next = new_node; // O próximo nó do final da fila é o novo nó
        queue->tail = new_node;       // O final da fila é o novo nó
    }

    // Desbloqueia o mutexs
    pthread_mutex_unlock(&queue->queue_mutex);
}

/*
 * Função que remove um elemento da fila
 * @param queue: fila
 * @return dado removido
 */
int dequeue(Queue *queue)
{
    // Bloqueia o mutex
    pthread_mutex_lock(&queue->queue_mutex);

    // Se a fila estiver vazia, retorna -1
    if (queue->head == NULL)
    {
        // Desbloqueia o mutex
        pthread_mutex_unlock(&queue->queue_mutex);
        return -1;
    }

    Node *node = queue->head; // Nó a ser removido
    int data = node->data;    // Dado a ser removido

    // Se a fila tiver apenas um elemento
    if (queue->head == queue->tail)
    {
        queue->head = NULL; // O início da fila é NULL
        queue->tail = NULL; // O final da fila é NULL
    }
    else // Se a fila tiver mais de um elemento
    {
        queue->head = queue->head->next; // O início da fila é o próximo nó
    }

    free(node); // Libera a memória do nó removido

    // Desbloqueia o mutex
    pthread_mutex_unlock(&queue->queue_mutex);

    return data; // Retorna o dado removido
}

/*
 * Função que destroi a fila
 * @param queue: fila
 * @return void
 */
void destroyQueue(Queue *queue)
{
    // Enquanto a fila não estiver vazia
    while (queue->head != NULL)
    {
        dequeue(queue); // Remove todos os elementos da fila
    }

    // Destroi o mutex
    pthread_mutex_destroy(&queue->queue_mutex);

    // Libera a memória da fila
    free(queue);
}

/*
 * Função que enfileira elementos na fila
 * @param queue: fila
 * @return void
 */
void *enqueue_thread(void *queue)
{
    Queue *q = (Queue *)queue; // Fila

    // Enfileira os elementos
    for (int i = 0; i < 10; i++)
    {
        enqueue(q, i);                   // Enfileira o elemento
        printf("Enfileirando: %d\n", i); // Mensagem de debug
    }
    pthread_exit(NULL); // Finaliza a thread
}

/*
 * Função que desenfileira elementos da fila
 * @param queue: fila
 * @return void
 */
void *dequeue_thread(void *queue)
{
    Queue *q = (Queue *)queue; // Fila

    for (int i = 0; i < 10; i++)
    {
        int data = dequeue(q); // Desenfileira o elemento

        if (data != -1)
        {
            printf("Desenfileirando: %d\n", data); // Mensagem de debug
        }
        else
        {
            printf("Fila vazia!\n"); // Mensagem de debug
        }
    }
    pthread_exit(NULL); // Finaliza a thread
}

int main()
{
    pthread_t t1, t2;             // Threadss
    Queue *queue = createQueue(); // Fila

    // Criação das threads
    pthread_create(&t1, NULL, enqueue_thread, (void *)queue); // Thread de enfileirar
    pthread_create(&t2, NULL, dequeue_thread, (void *)queue); // Thread de desenfileirar

    // Aguarda o término das threads
    pthread_join(t1, NULL); // Aguarda a thread 1
    pthread_join(t2, NULL); // Aguarda a thread 2

    // Destroi a fila
    destroyQueue(queue);

    return 0;
}