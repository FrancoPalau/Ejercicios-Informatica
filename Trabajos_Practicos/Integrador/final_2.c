/*Implemente una biblioteca con funciones para manipulación de listas doblemente enlazadas. Cree un
nodo para la lista mediante struct (el contenido de cada nodo es a libre elección del alumno), e
implemente funciones para
1. agregar un elemento a la lista,
2. eliminar un elemento de la lista,
3. modificar un elemento de la lista
4. mostrar todos los elementos de la lista.*/
#include <stdio.h>
#include <stdlib.h>
#include "final_2.h"

//Esta funcion agrega un nodo al principio de la lista
int agregar_principio(){
  int info;
  NODO *nuevo_elemento;
  nuevo_elemento=(NODO*)malloc(sizeof(NODO));
  printf("Ingrese elemento\n" );
  scanf("%d",&info );
  nuevo_elemento->dato=info;
    if(primero==NULL){
        primero=nuevo_elemento;
        primero->siguiente=NULL;
        primero->anterior=NULL;
    }else{
        primero->anterior=nuevo_elemento;
        nuevo_elemento->anterior=NULL;
        nuevo_elemento->siguiente=primero;
        primero=nuevo_elemento;
    }
    return 0;
}
//Esta funcion agrega un nodo al final de la lista
int agregar_final(){
  int info;
  NODO *nuevo_elemento;
  nuevo_elemento=(NODO*)malloc(sizeof(NODO));
  printf("Ingrese elemento\n" );
  scanf("%d",&info );
  nuevo_elemento->dato=info;
    if(ultimo==NULL){
        ultimo=nuevo_elemento;
        ultimo->siguiente=NULL;
        ultimo->anterior=NULL;
    }
    else{
        ultimo->siguiente=nuevo_elemento;
        nuevo_elemento->siguiente=NULL;
        nuevo_elemento->anterior=ultimo;
        ultimo=nuevo_elemento;
    }
    return 0;
}
//Esta funcion agrega un nodo a la lista despues del que se le dio como parametro
int agrega_despues_de(NODO *actual){
  int info;
  NODO *nuevo_elemento;
  nuevo_elemento=(NODO*)malloc(sizeof(NODO));
  printf("Ingrese elemento\n" );
  scanf("%d",&info );
  nuevo_elemento->dato=info;
    actual->siguiente->anterior=nuevo_elemento;
    nuevo_elemento->siguiente=actual->siguiente;
    actual->siguiente=nuevo_elemento;
    nuevo_elemento->anterior=actual;
    return 0;
}

//Esta funcion muestra los datos de cada nodo de la lista
int mostrar_datos(){
    NODO *actual;
    //actual=(NODO*)malloc(sizeof(NODO));
    actual=primero;
    if (primero!= NULL) {
        while (actual != NULL) {
            printf("%d\n",actual->dato );
            actual=actual->siguiente;
        }
    }else{
        printf("La lista esta vacia: \n" );
    }
    return 0;
}
//Esta funcion elimina el nodo que tiene el dato buscado
int eliminar_nodo(){
  NODO *actual;
  actual=primero;
  NODO *atras;
  atras=NULL;
  NODO *aux;
  int nodo_buscado=0,encontrado=0;
  printf("Ingrese el dato del nodo a buscar para eliminar \n");
  scanf("%d",&nodo_buscado );
  if (primero!= NULL) {
      while (actual!=NULL && encontrado!=1) {
          if (actual->dato==nodo_buscado) {
              if (primero==actual) {
                  aux=primero;
                  primero=primero->siguiente;
              }else if(ultimo==actual){
                  aux=ultimo;
                  atras->siguiente=NULL;
                  ultimo=atras;
              }else{
                  aux=actual;
                  atras->siguiente=actual->siguiente;
                  actual->siguiente->anterior=atras;
              }
              free(aux);
              printf("Nodo eliminado\n" );
              encontrado=1;
          }
          atras=actual;
          actual=actual->siguiente;
      }
      if (encontrado==0) {
          printf("Nodo no encontrado\n" );
      }
  }
  else{
      printf("Lista vacia\n" );
  }
  return 0;
}
//Esta funcion busca el nodo en donde esta el dato que se quiere modificar y lo cambia
int buscar_nodo(){
    NODO *actual;
    //actual=(NODO*)malloc(sizeof(NODO));
    actual=primero;
    int nodo_buscado=0,encontrado=0;
    printf("Ingrese el dato del nodo a buscar para modificar \n");
    scanf("%d",&nodo_buscado );
    if (primero!= NULL) {
        while (actual!=NULL && encontrado!=1) {
            if (actual->dato==nodo_buscado) {
                printf("El nodo con el dato %d encontrado \n" , nodo_buscado);
                printf("Ingrese el nuevo dato para este nodo \n" );
                scanf("%d",&actual->dato );
                printf("Nodo modificado\n" );
                encontrado=1;
            }
            actual=actual->siguiente;
        }
        if (encontrado==0) {
            printf("Nodo no encontrado\n" );
        }
    }
    else{
        printf("Lista vacia\n" );
    }
    return 0;
}
int borrar_lista(){
  NODO *aux;
  while (primero != NULL) {
      aux=primero->siguiente;
      free(primero);
      primero=aux;
  }
  return 0;
}
