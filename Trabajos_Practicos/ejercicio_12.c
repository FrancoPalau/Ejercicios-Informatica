#include <stdio.h>
#define  count 100

int main() {
  int i,j;
  int suma=0;

  for ( i = 0; i <= count; i++) {
    for ( j = 0; j <= count; j++) {
      if (i != j) {
        if (i%2==0 || j%2==0) {
          suma+=(i+j)/(i-j);
        }
      }
    }
  }
  printf("%d\n", suma);
  return 0;
}
