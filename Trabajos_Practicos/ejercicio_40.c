#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//Define un tipo de variable: VECTOR que tiene tres componentes x,y,z
typedef struct VECTOR{
    int x;
    int y;
    int z;
}vector_t;//Le cambio el nombre
void producto_vectorial(vector_t *vector1,vector_t *vector2,vector_t *vector3);//Prototipo de la funcion
int main() {
    //Crea dinamicamente el vector 1
    vector_t *vector1;
    vector1=(vector_t*)malloc(sizeof(vector_t));
    //Asigna las componentes del primer vector
    printf("Ingrese las componentes del primer vector: \n");
    scanf("%d%d%d", &vector1->x,&vector1->y,&vector1->z);
    //Crea dinamicamente el vector 2
    vector_t *vector2;
    vector2=(vector_t*)malloc(sizeof(vector_t));
    //Asigna las componentes del segundo vector
    printf("Ingrese las componentes del segundo vector: \n" );
    scanf("%d%d%d", &vector2->x,&vector2->y,&vector2->z);
    //Define el vector resultado dinamicamente
    vector_t *vector3;
    vector3=(vector_t*)malloc(sizeof(vector_t));
    //Llama a la funcion para calcular el producto vectorial de los dos vectores
    producto_vectorial(vector1,vector2,vector3);
    free(vector1);
    free(vector2);
    free(vector3);
    return 0;
}
//Esta funcion recibe dos vectores, calcula su producto vectorial y el resultado
//lo asigna a un tercer vector creado dinamicamente
void producto_vectorial(vector_t *vector1,vector_t *vector2,vector_t *vector3){

    //Producto vectorial de dos vectores
    vector3->x=vector1->y*vector2->z-vector1->z*vector2->y;
    vector3->y=vector1->z*vector2->x-vector1->x*vector2->z;
    vector3->z=vector1->x*vector2->y-vector1->y*vector2->x;
    //Imprime el vector resultado
    printf("El vector resultado es:\n");
    printf("X= %d   Y=%d   Z=%d \n",vector3->x,vector3->y,vector3->z );
}
