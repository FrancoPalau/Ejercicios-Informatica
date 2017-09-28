#include <stdio.h>
long fibonacci( long x);
int main() {
  long numero;
  printf("Ingrese un numero para calcular su sucesion de Fibonacci: " );
  scanf("%ld", &numero);
  printf("La sucesion de Fibonacci para %ld es: %ld\n", numero ,fibonacci(numero) );
  return 0;
}
long fibonacci( long x){
  if (x==0) {
    return 0;
  }
  if (x==1) {
    return 1;
  } else {
      return fibonacci(x-1) + fibonacci(x-2);
  }
}
