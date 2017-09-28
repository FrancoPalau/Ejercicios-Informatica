/*Escriba una función para recorrer el vector, sumar el contenido de aquellos elementos cuyo sub-índice
sea impar en una variable. Mostrar la variable al finalizar por pantalla*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int sumaImpar(int arreglo[],int tamano);
int main() {
  int n,i;

  srand( time( NULL ) );
  printf("Introduzca el largo del arreglo: ");
  scanf("%d", &n );

  int a[n];

  for (i = 0; i < n; i++) {
    a[i]=rand() %100;
    printf("%d\n", a[i]); /*Imprime el vector original*/
  }

  printf("La suma de los elementos de subindice impar es %d\n", sumaImpar(a,n));
  return 0;
}
int sumaImpar(int arreglo[],int tamano){
  int j,aux;
  aux=0;
    for ( j = 0; j < tamano; j++) {
      if ((j%2) != 0) {
        aux+=arreglo[j];
      }
    }
  return aux;
}
