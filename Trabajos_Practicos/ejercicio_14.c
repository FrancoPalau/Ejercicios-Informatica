#include <stdio.h>
int main() {
  int a,b;
  printf("Introduzca un entero: ");
  scanf("%d", &a );
  printf("Introduzca otro entero: ");
  scanf("%d", &b );
  printf("a&b: %d\n", a&b);
	printf("a|b: %d\n", a|b);
  printf("a^b: %d\n", a^b);

  return 0;
}
