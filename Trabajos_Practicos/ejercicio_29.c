#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void multiplica_matrix(int p,int matrix2[][p], int n,int matrix1[][n], int m);
int main() {
    int m,n,p,i,j,k;
    m=3;
    n=2;
    p=3;
    int matrix1[m][n];
    int matrix2[n][p];
    int matrix3[m][p];
    srand( time( NULL ) );
    printf("La primer matriz es: \n");
    for ( i = 0; i < m; i++) {
        for ( j = 0; j < n; j++) {
            matrix1[i][j]=rand() %10;
            printf("%d ",matrix1[i][j] );
        }
        printf("\n");
    }
    printf("\n");
    printf("La segunda matriz es: \n");
    for ( i = 0; i < n; i++) {
        for ( j = 0; j < p; j++) {
            matrix2[i][j]=rand() %10;
            printf("%d ",matrix2[i][j] );
        }
        printf("\n");
    }
    printf("\n");

printf("La multiplicacion de las dos matrices es: \n" );
multiplica_matrix(p,matrix2,n,matrix1,m);
  return 0;
}

void multiplica_matrix(int p,int matrix2[][p], int n,int matrix1[][n], int m){
  int i,j,k;
  int matrix3[m][p];
  printf("\n");
  for ( i = 0; i < m; i++) {
      for ( j = 0; j < p; j++) {
          matrix3[i][j]=0;
          for ( k = 0; k < n; k++) {
              matrix3[i][j]=matrix3[i][j]+(matrix1[i][k]*matrix2[k][j]);
          }
          printf("%d ",matrix3[i][j] );
      }
      printf("\n");
  }
}
