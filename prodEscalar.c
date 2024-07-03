#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define maxVetor 100

typedef int tipoVetor[maxVetor];

tipoVetor v1, v2;

int nElem;

int produtoEscalar(tipoVetor A, tipoVetor B, int n)
{   int PE, i;

    PE = 0;
    for (i=0; i<n; i++)
        PE=PE+A[i]*B[i];

    return (PE);
}

void geraVetor(char *tipo, tipoVetor V, int n)
{   int i;

    printf("\n%s: ", tipo);
    for (i=0; i<n; i++)
    {   V[i]=rand()%10;
        printf("%d, ",V[i]);
    }
    printf("\n");

}


void main(void)
{   int PE;

    srand(time(NULL));

    printf("\nQuantos elementos tem os vetores? => ");
    scanf("%d",&nElem);

    geraVetor("Vetor V1",v1, nElem);
    geraVetor("Vetor V2",v2, nElem);

    PE=produtoEscalar(v1, v2, nElem);

    printf("\n\nProduto Escalar = %d\n", PE);

}
