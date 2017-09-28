#include <stdio.h>
int main() {
  int i,x;
  int j=0;
  printf("Ingrese el valor de i: " );
  scanf("%d", &i);
  for ( x=0; x <= i; x++) {
    j+=x;
  }
  printf("La sumatoria da %d\n",j );
  return 0;
}
