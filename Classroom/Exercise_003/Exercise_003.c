#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *funcaoFibonacci(void *ptr) ;

struct tipoPack {
   char mensagem[16] ;
   int pos, fib ;
};


void main(void)
{
     pthread_t thread1, thread2 ;
     int  iret1, iret2 ;

     //
     struct tipoPack pack1 = {"\nSou a thread 1", 0, 0} ; 
     struct tipoPack pack2 = {"\nSou a thread 2", 0, 0} ;

     // 
     printf("\nDigite a posição do termo de fibonacci 1 > ") ;
     scanf("%d",&(pack1.pos)) ;
     printf("\nDigite a posição do termo de fibonacci 2 > ") ;
     scanf("%d",&(pack2.pos)) ;

     // 
     iret1 = pthread_create(&thread1, NULL, funcaoFibonacci, (void*) &pack1) ;
     iret2 = pthread_create(&thread2, NULL, funcaoFibonacci, (void*) &pack2) ;
	
     //
     pthread_join(thread1, NULL) ;
     pthread_join(thread2, NULL) ;
	
     // 
     printf("\nThread 1 fibonacci de %d -> %d \n", pack1.pos, pack1.fib) ;
     printf("\nThread 2 fibonacci de %d -> %d \n", pack2.pos, pack2.fib) ;
}

void *funcaoFibonacci(void *ptr)
{    
	int i;
     	struct tipoPack *pack ;
     	pack= (struct tipoPack *) ptr ;

     	printf("%s: Realizando o calculo do termo de fibonacci \n", pack->mensagem) ;
	
	int n = (pack->pos) ;
	int a = 0 ;
	int b = 1 ; 
     	for (i = 2; i <= n; i++)
     	{
		int temp = a + b ;
		a = b ;
		b = temp ;
	}

	(pack->fib) = (n==0) ? a : b ;

	pthread_exit(NULL) ;
}
