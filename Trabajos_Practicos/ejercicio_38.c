#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void multiplica_matrix(float **matrix1,float **matrix2,int f1,int c1,int c2);
int main() {
    int f1,c1,f2,c2,i,j;
	float valor;
    //Guarda las dimensiones de las dos matrices
    printf("Ingrese filas y luego columnas de la matrix1: \n" );
    scanf("%d%d",&f1,&c1 );
    printf("Ingrese filas y luego columnas de la matrix2: \n" );
    scanf("%d%d",&f2,&c2 );
    //Verifica que la multiplicacion sea posible
    if (c1!= f2){
        printf("ERROR:las columnas de la primer matriz deben ser iguales a las filas de la segunda matriz \n" );
    }else{
        srand( time( NULL ) );
        //Define dinamicamente la 1 matriz
        float **matrix1;
        matrix1 = (float **)calloc(f1, sizeof(float *));
        for(i = 0; i < f1; i++){
            matrix1[i] = (float *)calloc(c1, sizeof(float));
        }
        //Crea los valores aleatorios de la primer matriz
        printf("La primer matriz es: \n");
        for ( i = 0; i < f1; i++) {
            for ( j = 0; j < c1; j++) {
				scanf("%f",&valor);
                matrix1[i][j]=valor;
                //printf("%d ",matrix1[i][j] );
            }
            //printf("\n");
        }
        //Define dinamicamente la 2 matriz
        float **matrix2;
        matrix2 = (float **)calloc(f2, sizeof(float *));
        for(i = 0; i < f2; i++){
            matrix2[i] = (float *)calloc(c2, sizeof(float));
        }
        //Crea los valores aleatorios de la segunda matriz
        printf("La segunda matriz es: \n");
        for ( i = 0; i < f2; i++) {
            for ( j = 0; j < c2; j++) {
				scanf("%f",&valor);	                
				matrix2[i][j]=valor;
                //printf("%d ",matrix2[i][j] );
            }
            //printf("\n");
        }
        //Llama a la funcion que multiplica las matrices
        printf("La matriz resultado es: \n" );
        multiplica_matrix(matrix1,matrix2,f1,c1,c2);
        for(i = 0; i < f2; i++){
            free(matrix2[i]);
        }
        free(matrix2);
        for(i = 0; i < f1; i++){
            free(matrix1[i]);
        }
        free(matrix1);
    }
  return 0;
}
//Esta funcion recibe dos matrices con sus dimensiones y las multiplica
void multiplica_matrix(float **matrix1,float **matrix2,int f1,int c1,int c2){
    float matrix3[f1][c2];
    int i,j,k;
    //multiplica las dos matrices
    for ( i = 0; i < f1; i++) {
        for ( j = 0; j < c2; j++) {
            matrix3[i][j]=0;
            for ( k = 0; k < c1; k++) {
                matrix3[i][j]=matrix3[i][j]+(matrix1[i][k]*matrix2[k][j]);
            }
            printf("%f ",matrix3[i][j] );
        }
        printf("\n");
    }

}
