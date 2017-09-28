#include <stdio.h>
long factorial(int x);
int main()
{
  int numero;
  printf("%s","Introduzca el numero para calcular su factorial: " );
  scanf("%d", &numero);
  printf("El factorial de %d es %ld\n", numero, factorial(numero) );
  return 0;
}
long factorial(int x){
  if (x==0 || x==1) {
    return 1;
  } else {
    return x*factorial(x-1);
  }
}
