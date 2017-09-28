#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    char cadena[100];
    int largo,i;
    int aux;
    //char aux2;
    printf("Ingrese la cadena: \n" );
    scanf("%s",cadena );
    largo=strlen(cadena);
    /*int contador=0;
    do {
        aux2=cadena[contador];
        contador++;
    } while(aux2!='\0');
    printf("%d\n", contador);*/
    char cadena_invertida[largo+1];
    cadena_invertida[largo]='\0';
    aux=largo-1;
    for ( i = 0; i < largo; i++) {
        cadena_invertida[i]=cadena[aux];
        aux--;
    }
    printf("%s\n", cadena_invertida);
    return 0;
}
