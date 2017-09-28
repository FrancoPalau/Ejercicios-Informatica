#include <stdio.h>
int main() {
  int a,b,c,i;
  int cant=0;
  printf("Introduza a: ");
  scanf("%d",&a);
  printf("Introduza b: ");
  scanf("%d",&b);
  printf("Introduza c: ");
  scanf("%d",&c);

  for (i = a; i <= b; i++) {
    if (i%c == 0) {
      ++cant;
    }
  }
  printf("La cantidad de numeros divisibles por %d entre %d y %d es: %d\n",c ,a ,b ,cant );
  return 0;
}
