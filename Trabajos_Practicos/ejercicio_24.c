/*Escriba una función para recorrer el vector y guardar el promedio de los valores en una variable. Mostrar
el promedio por pantalla.*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
float promedio(int arreglo[],int tamano);
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

  printf("El promedio de los elementos es %.2f\n", promedio(a,n));
  return 0;
}
float promedio(int arreglo[],int tamano){
  int j;
  float aux=0;
    for ( j = 0; j < tamano; j++) {
        aux+=arreglo[j];
    }
  return aux/tamano;
}
