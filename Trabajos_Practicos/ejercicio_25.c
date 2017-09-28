#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int menor(int arreglo[],int tamano);
int main() {
  int n,i,chico;

  srand( time( NULL ) );
  printf("Introduzca el largo del arreglo: ");
  scanf("%d", &n );

  int a[n];

  for (i = 0; i < n; i++) {
    a[i]=rand() %1000;
    printf("%d\n", a[i]); /*Imprime el vector original*/
  }

  printf("El menor de los numeros es %d\n", menor(a,n));
  return 0;
}
int menor(int arreglo[],int tamano){
  int i,pasadas,j,aux;
  for ( pasadas = 0; pasadas < (tamano-1); pasadas++) {
    for ( j = 0; j < (tamano-1); j++) {
      if (arreglo[j] > arreglo[j+1]) {
        aux=arreglo[j];
        arreglo[j]=arreglo[j+1];
        arreglo[j+1]=aux;
      }
    }
  }
  return arreglo[0];
}
