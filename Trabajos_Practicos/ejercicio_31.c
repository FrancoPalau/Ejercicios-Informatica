#include <stdio.h>
#include <time.h>
#include <stdlib.h>
void multiplica_vector(float *vector1,float *vector2,float *vector3);
int main() {
    float vector1[3],vector2[3],vector3[3];
    int i;
    srand(time(NULL));
    printf("vector1\n" );
    for (i = 0; i < 3; i++) {
        vector1[i]=rand() %10;
        printf("%.2f ", vector1[i]);
        vector2[i]=rand() %10;
    }
    printf("\nvector2\n" );
    for (i = 0; i < 3; i++) {
        vector2[i]=rand() %10;
        printf("%.2f ", vector2[i]);
    }
    multiplica_vector(vector1,vector2,vector3);

  return 0;
}
void multiplica_vector(float *vector1,float *vector2,float *vector3){
  //Producto vectorial de dos vectores
  vector3[0]=vector1[1]*vector2[2]-vector1[2]*vector2[1];
  vector3[1]=vector1[2]*vector2[0]-vector1[0]*vector2[2];
  vector3[2]=vector1[0]*vector2[1]-vector1[1]*vector2[0];
  //Imprime el vector resultado
  printf("\nEl vector resultado es:\n");
  printf("X= %.2f   Y=%.2f   Z=%.2f \n",vector3[0],vector3[1],vector3[2] );
}
