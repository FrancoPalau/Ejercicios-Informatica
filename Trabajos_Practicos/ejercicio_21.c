#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void pares(int variable[], int tamano);
int main() {
  int n,i;

  srand( time( NULL ) );
  printf("Introduzca el largo del arreglo: ");
  scanf("%d", &n );
  int a[n];
  for (i = 0; i < n; i++) {
    a[i]=rand() %1000;
    printf("%d\n", a[i]);
  }
  printf("El vector solo de pares es:\n");
  pares(a,n);
  return 0;
}
void pares(int variable[], int tamano){
  int i;
  for (i = 0; i < tamano; i++) {
    if (variable[i]%2==0) {
      printf("%d\n", variable[i]);
    }
  }
}
