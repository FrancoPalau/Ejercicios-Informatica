#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
  return 0;
}
