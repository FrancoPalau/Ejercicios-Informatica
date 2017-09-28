#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void matriz_par(int columna,int matrix[][columna],int fila);
int main() {
    int fila,columna;
    printf("Ingrese las dimensiones de la matriz:\n" );
    scanf("%d%d", &fila,&columna);
    int matrix[fila][columna];
    matriz_par(columna,matrix,fila);
  return 0;
}
void matriz_par(int columna,int matrix[][columna],int fila){
    srand(time(NULL));
    int i,j;
    for ( i = 0; i < fila; i++) {
        for ( j = 0; j < columna; j++) {
            if ((i+j)%2 == 0) {
                matrix[i][j]=rand() %100;
            } else {
                matrix[i][j]=0;
            }
            printf("%d ", matrix[i][j]);
        }
        printf("\n" );
    }
}
