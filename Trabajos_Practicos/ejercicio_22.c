#include<stdio.h>
#include <stdlib.h>
int main(){

    int n;
    printf("Ingrese el numero de elementos del vector: ");
    scanf("%d", &n);
    int vector[n];
    int i;
    printf("Ingrese los elementos: \n" );
    for (i=0;i<n;i++){
        scanf("%d",&vector[i]);
    }
    int k=0;
    for (i=0;i<n;i++){
            printf("%d ",vector[i]);
            if (vector[i]<5){
                k++;
            }
    }

    printf("\n");



    int *vector2;
    vector2=(int*)calloc(k,sizeof(int));
    int l=0;
    int p=0;
    while (p<k /*&& l<n*/){
        if(vector[l]%2==1){
            vector2[p]=vector[l];
            p++;
        }
        l++;
    }
    for (i=0;i<k;i++){
        printf("%d ",vector2[i]);
    }
    free(vector2);

}
