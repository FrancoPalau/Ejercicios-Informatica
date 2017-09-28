#include<stdio.h>
#include<math.h>
#include <stdlib.h>
int main(){
    int largo=100;
    int *vector;
    vector = (int *)calloc(largo,sizeof(int));
    int orden,cont;
    printf("Ingrese el orden del polinomio\n");
    scanf("%d",&orden);
    int i;
    printf("Ingrese los valores de los coeficientes \n");
    for (i=0;i<orden+1;i++){
        scanf("%d",&vector[i]);
    }
    printf(" Ingrese el valor de x \n");
    float x;
    scanf("%f",&x);
    float suma=0;
    cont=0;
    for (i=orden;i>=0;i--){
        suma =suma+vector[cont]*pow(x,i);
        cont++;
    }
    printf("Esta es la suma %.2f\n",suma);

}
