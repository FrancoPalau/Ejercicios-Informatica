#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int main() {
    int largo=100;
    int *vector;
    vector=(int *)calloc(largo,sizeof(int));
    int orden,i,aux;
    float x1,x2,delta,j;
    printf("Ingrese el orden del polinomio: \n" );
    scanf("%d",&orden );
    printf("Ingrese los coeficientes: \n" );
    for ( i = 0; i < (orden+1); i++) {
        scanf("%d", &vector[i]);
    }
    printf("Ingrese primero el extremo menor del intervalo y luego el mayor:\n");
    scanf("%f%f",&x1,&x2 );
    printf("Ingrese el incremento del intervalo: \n");
    scanf("%f",&delta );
    aux=(x2-x1)/delta;
    float *suma;
    suma=(float *)calloc(aux,sizeof(float));
    suma[aux]=0;
    int cont;
    int contador=0;
    printf("El vector de resultados es: \n");
    for (j = x1; j <= x2; j=j+delta) {
        cont=0;
        for (i=orden ;i>=0; i--){
            suma[contador] =suma[contador]+vector[cont]*pow(j,i);
            cont++;
        }
        printf("%.2f\n", suma[contador]);
        contador++;
    }
    free(suma);
    return 0;
}
