#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void matriz_par(int columna,int matrix[][columna],int fila);
void transpuesta(int columna,int matrix[][columna],int fila,int matrix_trans[][fila]);
int main() {
    int fila,columna;
    printf("Ingrese las dimensiones de la matriz:\n" );
    scanf("%d%d", &fila,&columna);
    int matrix[fila][columna];
    matriz_par(columna,matrix,fila);
    int matrix_trans[columna][fila];
    transpuesta(columna,matrix,fila,matrix_trans);
  return 0;
}
void matriz_par(int columna,int matrix[][columna],int fila){
    srand(time(NULL));
    int i,j;
    printf("La matriz generada es: \n" );
    for ( i = 0; i < fila; i++) {
        for ( j = 0; j < columna; j++) {
            if ((i+j)%2 == 0) {
                matrix[i][j]=rand() %100;
            } else {
                matrix[i][j]=0;
            }
            printf("[%d ]", matrix[i][j]);
        }
        printf("\n" );
    }
}
void transpuesta(int columna,int matrix[][columna],int fila,int matrix_trans[][fila]){
    int i,j;
    printf("La matriz transpuesta es: \n");
    for ( i = 0; i < columna; i++) {
        for ( j = 0; j < fila; j++) {
            matrix_trans[i][j]=matrix[j][i];
            printf("[%d ]", matrix_trans[i][j]);
        }
        printf("\n" );
    }
}
