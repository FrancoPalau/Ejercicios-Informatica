#include <stdio.h>
int main(void){
  int  a,b,c,d,e,min,max;
  printf("%s\n","Escriba 4 numeros enteros en orden" );
  scanf("%d%d%d%d", &a, &b, &c, &d);
  printf("%s\n","Escriba un numero cualquiera" );
  scanf("%d", &e);

  if (a<=e && e<=b){
    printf("%s%d%s%d%s%d\n","El intervalo es ",a,"<=",e,"<=",b );
} else if (b<=e && e<=c) {
    printf("%s%d%s%d%s%d\n","El intervalo es ",b,"<=",e,"<=",c );
} else if (c<=e && e<=d) {
    printf("%s%d%s%d%s%d\n","El intervalo es ",c,"<=",e,"<=",d );
} else
    printf("%s\n","El numero que dio no esta dentro de los numeros ordenados" );
}
