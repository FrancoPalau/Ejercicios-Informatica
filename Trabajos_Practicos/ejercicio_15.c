#include <stdio.h>
float a,b,c,x,polinomio;
int main() {
  printf("Ingrese el coeficiente a: " );
  scanf("%f", &a);
  printf("Ingrese el coeficiente b: " );
  scanf("%f", &b);
  printf("Ingrese el coeficiente c: " );
  scanf("%f", &c);
  printf("Ingrese el valor de x: " );
  scanf("%f", &x);
  polinomio=a*x*x+b*x+c;
  printf("El valor del polinomio es %.3f\n",polinomio );
  return 0;
}
