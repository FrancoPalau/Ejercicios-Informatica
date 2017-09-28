/*Implementar el ejercicio 38 (multiplicación de matrices dinámicas) utilizando multithreading. Cada thread
debe producir una fila de la matriz resultado: si A es de mxn y B es de nxp, el resultado de A x B es una
matriz C de mxp, por lo que se crearán m threads para la multiplicación. Imprima el resultado por
pantalla.*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
//Variables globales
int **matrix1,**matrix2,**matrix3;
int p;
int f1,c1,f2,c2;
//Creacion de Mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//Firmas de las funciones
void *funcion_hilo(void *id_thread);
void multiplica_matrix(int **matrix1,int **matrix2,int f1,int c1,int c2,int **matrix3);

int main() {
  int i,j;
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
      matrix1 = (int **)calloc(f1, sizeof(int *));
      for(i = 0; i < f1; i++){
          matrix1[i] = (int *)calloc(c1, sizeof(int));
      }
      //Crea los valores aleatorios de la primer matriz
      printf("La primer matriz es: \n");
      for ( i = 0; i < f1; i++) {
          for ( j = 0; j < c1; j++) {
              matrix1[i][j]=rand() %10;
              printf("%d ",matrix1[i][j] );
          }
          printf("\n");
      }
      //Define dinamicamente la 2 matriz
      matrix2 = (int **)calloc(f2, sizeof(int *));
      for(i = 0; i < f2; i++){
          matrix2[i] = (int *)calloc(c2, sizeof(int));
      }
      //Crea los valores aleatorios de la segunda matriz
      printf("La segunda matriz es: \n");
      for ( i = 0; i < f2; i++) {
          for ( j = 0; j < c2; j++) {
              matrix2[i][j]=rand() %10;
              printf("%d ",matrix2[i][j] );
          }
          printf("\n");
      }
      //Define dinamicamente la 3 matriz
      matrix3 = (int **)calloc(f1, sizeof(int *));
      for(i = 0; i < f1; i++){
          matrix3[i] = (int *)calloc(c2, sizeof(int));
      }

      printf("La matriz resultado es: \n" );
      //Creacion de los threads
      pthread_t hilos[f1];
      for ( i = 0; i < f1; i++) {
          if (pthread_create(&hilos[i],NULL,funcion_hilo,NULL)) {
            printf("Error al crear el hilo \n");
            abort();
          }
      }
      for (i = 0; i < f1; i++) {
          if (pthread_join(hilos[i], NULL)) {
              printf("ERROR \n" );
          }
      }
      //Liberamos la memoria
      for(i = 0; i < f1; i++){
          free(matrix1[i]);
          free(matrix3[i]);
      }
      free(matrix1);
      free(matrix3);
      for(i = 0; i < f2; i++){
          free(matrix2[i]);
      }
      free(matrix2);
    }
  return 0;
}
void *funcion_hilo(void *info){
    //Bloqueo del Mutex
    pthread_mutex_lock(&mutex);
    //Lo que realiza la funcion
    multiplica_matrix(matrix1,matrix2,p,c1,c2,matrix3);
    p++; //variable critica
    //Liberamos el Mutex
    pthread_mutex_unlock(&mutex);
    return NULL;
}
void multiplica_matrix(int **matrix1,int **matrix2,int f1,int c1,int c2,int **matrix3){
    int j,k;
    //multiplica las dos matrices

        for ( j = 0; j < c2; j++) {
            matrix3[f1][j]=0;
            for ( k = 0; k < c1; k++) {
                matrix3[f1][j]=matrix3[f1][j]+(matrix1[f1][k]*matrix2[k][j]);
            }
            printf("%d ",matrix3[f1][j] );
        }
        printf("\n");
}
