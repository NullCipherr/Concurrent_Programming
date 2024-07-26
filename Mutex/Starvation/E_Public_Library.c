// Exercício - Biblioteca Pública
//
// Imagine uma biblioteca pública onde estudantes estão competindo por acesso a um número limitado de computadores.
// Se estudantes de alta prioridade(por exemplo, que têm provas importantes) sempre conseguem usar os computadores, estudantes de baixa prioridade podem acabar famintos.
// Sua tarefa é implementar um sistema justo onde todos os estudantes eventualmente têm acesso aos computadores.
// Utilize variáveis de condição e mutexes para gerenciar o acesso justo aos computadores da biblioteca.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define TIME 1000000 // 1s

#define NUM_STUDENTS 20 // Número de estudantes
#define NUM_COMPUTERS 8 // Número de computadores

pthread_mutex_t res_mutex; // Mutex
pthread_cond_t cond;       // Variável de condição

int free_computers = NUM_COMPUTERS; // Número de computadores livres

/*
 * Função executada pelo estudante
 * @param arg: argumento passado para a thread
 * @return void
 */
void *student_task(void *arg)
{
    int id = *((int *)arg);
    int priority = rand() % 2; // Prioridade do estudante = 0 ou 1, onde, 0 = baixa prioridade e 1 = alta prioridade.

    while (1)
    {
        pthread_mutex_lock(&res_mutex); // Bloqueia o mutex

        if (free_computers == 0) // Se não houver computadores disponíveis
        {
            printf("Estudante %d está esperando por um computador.\n", id);
            pthread_cond_wait(&cond, &res_mutex); // Espera até que um computador esteja disponível
        }

        free_computers--; // Decrementa o número de computadores disponíveis

        printf("Estudante %d está usando um computador. Prioridade = %d\n", id, priority);

        pthread_mutex_unlock(&res_mutex); // Desbloqueia o mutex

        usleep(TIME); // Estudante está usando o computador

        pthread_mutex_lock(&res_mutex); // Bloqueia o mutex
        free_computers++;               // Incrementa o número de computadores disponíveis

        printf("Estudante %d liberou o computador. Prioridade = %d\n", id, priority);

        pthread_cond_broadcast(&cond);    // Sinaliza que um computador foi liberado
        pthread_mutex_unlock(&res_mutex); // Desbloqueia o mutex

        usleep(TIME); // Estudante está fora do computador
    }

    pthread_exit(NULL);
}

/*
 * Função principal
 */
int main()
{
    pthread_t student[NUM_STUDENTS]; // Vetor de threads
    int student_id[NUM_STUDENTS];    // Vetor de identificadores de threads

    pthread_mutex_init(&res_mutex, NULL); // Inicializa o mutex
    pthread_cond_init(&cond, NULL);       // Inicializa a variável de condição

    for (int i = 0; i < NUM_STUDENTS; i++)
    {
        student_id[i] = i;
        pthread_create(&student[i], NULL, student_task, &student_id[i]);
    }

    for (int i = 0; i < NUM_STUDENTS; i++)
    {
        pthread_join(student[i], NULL);
    }

    pthread_mutex_destroy(&res_mutex); // Destrói o mutex
    pthread_cond_destroy(&cond);       // Destrói a variável de condição

    return 0;
}