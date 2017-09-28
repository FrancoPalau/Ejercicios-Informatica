#include <stdio.h>
#include <stdlib.h>
void multiplica_matrix(int p,int matrix1[][p], int n,int matrix2[][1], int m);
int main() {
    int sx,sy,sz,i,j;
    int vector[4][1];
    int matrix1[4][4];
    printf("Introduzca las 3 componentes del vector:\n" );
    scanf("%d%d%d",&vector[0][0],&vector[1][0],&vector[2][0] );
    vector[3][0]=1;
    printf("Introduzca los tres factores de escala:\n" );
    scanf("%d%d%d",&sx,&sy,&sz );

    for ( i = 0; i < 4; i++) {
        for ( j = 0; j < 4; j++) {
            if (i==j) {
                if (j==0) {
                    matrix1[i][j]=sx;
                }else if (j==1) {
                    matrix1[i][j]=sy;
                }else if (j==2) {
                    matrix1[i][j]=sz;
                }else{
                    matrix1[i][j]=1;
                }
            }else{
                matrix1[i][j]=0;
            }
            //printf("%d ", matrix1[i][j]);
        }
        //printf("\n" );
      }

      printf("\n" );
      multiplica_matrix(4,matrix1,4,vector,4);
  return 0;
}
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
