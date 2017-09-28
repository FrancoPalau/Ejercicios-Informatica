#include <stdio.h>
#include <stdlib.h>
void multiplica_matrix(int p,int matrix1[][p], int n,int matrix2[][1], int m);
int main() {
    //Definicion de variables
    int sx,sy,sz,i,j;
    int vector[4][1];
    int matrix1[4][4];
    //Lee el vector de 3 dimensiones
    printf("Introduzca las 3 componentes del vector:\n" );
    scanf("%d%d%d",&vector[0][0],&vector[1][0],&vector[2][0] );
    vector[3][0]=1;
    //Lee los factores de traslacion
    printf("Introduzca los tres factores de traslacion:\n" );
    scanf("%d%d%d",&sx,&sy,&sz );
    //Crea la matriz de traslacion
    for ( i = 0; i < 4; i++) {
        for ( j = 0; j < 4; j++) {
            if (i==j) {
                matrix1[i][j]=1;
            }else{
                if (j==3 && i==0) {
                    matrix1[i][j]=sx;
                }else if (j==3 && i==1){
                    matrix1[i][j]=sy;
                }else if(j==3 && i==2){
                    matrix1[i][j]=sz;
                }else{
                    matrix1[i][j]=0;
                }
            }
            //printf("%d ", matrix1[i][j]);
      }
        //printf("\n" );
    }
    //Llama a la funcion que multiplica la matriz con el vector
    multiplica_matrix(4,matrix1,4,vector,4);
    return 0;
}
//Funcion que multiplica una matriz y un vector
void multiplica_matrix(int p,int matrix1[][p], int n,int matrix2[][1], int m){
    int i,j,k;
    int matrix3[n][1];
    printf("\n");
    for ( i = 0; i < n; i++) {
        for ( j = 0; j < 1; j++) {
            matrix3[i][j]=0;
            for ( k = 0; k < m; k++) {
                matrix3[i][j]=matrix3[i][j]+(matrix1[i][k]*matrix2[k][j]);
            }
            printf("%d ",matrix3[i][j] );
        }
        printf("\n");
    }
}
