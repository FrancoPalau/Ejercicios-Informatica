#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void multiplica_matrix(int p,double matrix2[][p], int n,double matrix1[][n], int m,double matrix3[][p],int r);
int main() {
    //Definicion de variables
    double sx,sy,sz;
    int i,j;
    double vector[4][1];

    //Lee el vector de 3 dimensiones
    printf("Introduzca las 3 componentes del vector:\n" );
    scanf("%lf%lf%lf",&vector[0][0],&vector[1][0],&vector[2][0] );
    vector[3][0]=1;
    //Lee los factores de rotacion
    printf("Introduzca los tres factores de rotacion:\n" );
    scanf("%lf%lf%lf",&sx,&sy,&sz );
    //Crea la matriz alfa
    double matrix_alfa[4][4]={{1,0,0,0},{0,cos(sx),sin(sx),0},{0,-sin(sx),cos(sx),0},{0,0,0,1}};
    //Crea la matriz beta
    double matrix_beta[4][4]={{cos(sy),0,sin(sy),0},{0,1,0,0},{-sin(sy),0,cos(sy),0},{0,0,0,1}};
    //Crea la matriz tita
    double matrix_tita[4][4]={{cos(sz),sin(sz),0,0},{-sin(sz),cos(sz),0,0},{0,0,1,0},{0,0,0,1}};
    //Crea matrices auxiliares para la multiplicacion
    double matrix_aux1[4][4];
    double matrix_aux2[4][4];
    //El vector final
    double vector_resultado[4][1];
    //1° llamada: alfa x beta
    multiplica_matrix(4,matrix_beta,4,matrix_alfa,4,matrix_aux1,4);
    //2° llamada: ((alfa x beta) x tita)
    multiplica_matrix(4,matrix_tita,4,matrix_aux1,4,matrix_aux2,4);
    //3° llamada: (((alfa x beta) x tita) x vector)
    multiplica_matrix(1,vector,4,matrix_aux2,4,vector_resultado,4);
    //Imprime el vector final
    printf("\n");
    for ( i = 0; i < 4; i++) {
        printf("%.3lf\n ",vector_resultado[i][0] );
    }

    return 0;
}
//Funcion que recibe tres matrices, las dos a multiplicar y la matriz resultante
void multiplica_matrix(int p,double matrix2[][p], int n,double matrix1[][n], int m,double matrix3[][p],int r){
  int i,j,k;

  for ( i = 0; i < r; i++) {
      for ( j = 0; j < p; j++) {
          matrix3[i][j]=0;
          for ( k = 0; k < n; k++) {
              matrix3[i][j]=matrix3[i][j]+(matrix1[i][k]*matrix2[k][j]);
          }
          //printf("%lf ",matrix3[i][j] );
      }
      //printf("\n");
  }

}
