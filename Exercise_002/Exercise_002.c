#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *funcaoFatorial(void *ptr) ;

struct tipoPack {
   char mensagem[16] ;
   int tam, fat ;
};


void main(void)
{
     pthread_t thread1, thread2 ;
     int  iret1, iret2 ;

     //
     struct tipoPack pack1 = {"\nSou a thread 1", 0, 0} ; 
     struct tipoPack pack2 = {"\nSou a thread 2", 0, 0} ;

     // 
     printf("\nDigite o tamanho da sequencia 1 > ") ;
     scanf("%d",&(pack1.tam)) ;
     printf("\nDigite o tamanho da sequencia 2 > ") ;
     scanf("%d",&(pack2.tam)) ;

     // 
     iret1 = pthread_create(&thread1, NULL, funcaoFatorial, (void*) &pack1) ;
     iret2 = pthread_create(&thread2, NULL, funcaoFatorial, (void*) &pack2) ;
	
     //
     pthread_join(thread1, NULL) ;
     pthread_join(thread2, NULL) ;
	
     // 
     printf("\nThread 1 fatorial de %d -> %d \n", pack1.tam, pack1.fat) ;
     printf("\nThread 2 fatoral de %d -> %d \n", pack2.tam, pack2.fat) ;
}

void *funcaoFatorial(void *ptr)
{    
	int i;
     	struct tipoPack *pack ;
     	pack= (struct tipoPack *) ptr ;

     	printf("%s: Realizando o fatorial", pack->mensagem) ;

	(pack->fat) = 1 ;
     	for (i=1; i<=(pack->tam); i++)
     	{
		(pack->fat) *=  i ;
	}

	pthread_exit(NULL) ;
}
