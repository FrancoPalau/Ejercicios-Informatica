#include <stdio.h>
float polinomio(float x, float a, float b, float c);
int main() {
  float x1,x2,delta,i,resultado;
  float a,b,c;
  printf("Ingrese el coeficiente a: " );
  scanf("%f", &a);
  printf("Ingrese el coeficiente b: " );
  scanf("%f", &b);
  printf("Ingrese el coeficiente c: " );
  scanf("%f", &c);
  printf("Ingrese el extremo inferior: " );
  scanf("%f", &x1);
  printf("Ingrese el extremo superior: " );
  scanf("%f", &x2);
  printf("Ingrese el incremento: " );
  scanf("%f", &delta);
  printf("%s\t%s\n","X","Polinomio" );
  for (i = x1; i <= x2; i+=delta) {
    resultado=polinomio(i,a,b,c);
    printf("%.3f\t%.3f\n",i,resultado );
  }
  return 0;
}
float polinomio(float x, float a, float b, float c){
  return a*x*x+b*x+c;
}
