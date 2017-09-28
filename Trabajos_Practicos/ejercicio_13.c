#include <stdio.h>
int main() {
  int a,i;
  long m;
  printf("Introduzca un entero: ");
  scanf("%d", &a );
  m=2147483648;
  printf("Su numero en binario es: ");
  for (i = 31; i >= 0; i--) {
    if (m & a) {
      printf("1");
    } else {
      printf("0");
    }
    a<<=1;
  }
  printf("\n");
  return 0;
}
