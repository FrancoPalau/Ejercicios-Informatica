#include <stdio.h>
int main()
{
  int numero, i;
  long factorial=1;

  printf("%s","Introduzca el numero para calcular su factorial:\n" );
  scanf("%d", &numero);
  for ( i = numero; i >= 1 ; i--) {
    factorial*=i;
  }
  printf("El factorial de %d es %ld\n", numero, factorial );
  return 0;
}
