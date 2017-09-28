#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
    int largo,resultado,i;
    printf("Ingrese el tamaño de los vectores: \n");
    scanf("%d",&largo );
    int vector1[largo];
    int vector2[largo];
    srand(time(NULL));
    resultado=0;
    printf("Los vectores son: \n");
    for ( i = 0; i < largo; i++) {
        vector1[i]=rand() %10;
        printf("[%d]  ",vector1[i] );
        vector2[i]=rand() %10;
        printf("  [%d]\n",vector2[i] );
        resultado=resultado+vector1[i]*vector2[i];
    }
    printf("\nEl producto escalar da:  " );
    printf("%d\n", resultado);
  return 0;
}
