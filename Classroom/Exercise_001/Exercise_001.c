#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *funcaoImprimeMensagem( void *ptr ) ;

// Declara um vetor de 3000 posições.
int v[3000] ; 

void main(void)
{
    // Declaração de váriaveis
    pthread_t thread1, thread2, thread3 ;
    int pos_thread_1 = 1 ;
    int pos_thread_2 = 2 ;
    int pos_thread_3 = 3 ;
    
    int  iret1, iret2, iret3 ;

    // Cria 3 threads independentes e ambas executarao a mesma funcao com argumentos diferentes.
    iret1 = pthread_create(&thread1, NULL, funcaoImprimeMensagem, (void*) &pos_thread_1);
    iret2 = pthread_create(&thread2, NULL, funcaoImprimeMensagem, (void*) &pos_thread_2);
    iret3 = pthread_create(&thread3, NULL, funcaoImprimeMensagem, (void*) &pos_thread_3);

    // Mensagem de retorno das threads.
    printf("\nCriacao da thread 1 retornou: %d\n",iret1) ;
    printf("\nCriacao da thread 2 retornou: %d\n",iret2) ;
    printf("\nCriacao da thread 3 retornou: %d\n",iret3) ;

    /* Espera as threads completarem para entao continuar, para nao
       correr o risco de terminar o programa principal antes das
       threads terminarem. O termino do processo causa forcadamente
       o termino de suas tarefas */
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    printf("\nTodas as 3 Threads foram finalizadas...\n") ;
    
    printf("Imprimindo o vetor de elementos... \n") ;
    for(int i = 0; i < 3000; i++)
    {
        // Pos[i] -> n_Thread
        printf("Pos[%d] -> %d \n", i, v[i]) ;
    }
    
    exit(0) ;
}

void *funcaoImprimeMensagem(void *ptr )
{
    int *n_Thread ; 
    n_Thread = (int*) ptr ;
    int valor_Thread = *n_Thread ;
    
    for(int i = 0; i < 1000 ; i++)
    {
        v[i+((valor_Thread-1)*1000)] = valor_Thread ; 
    }
}
