#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int boolean;
#define FALSE 0
#define TRUE 1
boolean hay_sustituciones;

int guardar_valor,valor_pivote,posicion_elemento_buscado=-1;
int busqueda_binaria(int *arreglo, int lim_inf, int lim_sup, int posicion_piv, int elemento_buscado);
void bubblesort(int arreglo[],int tamano);
void quicksort(int *arreglo, int i_izq, int i_der, int posicion_piv);

int main() {
    int n=1000;
    int elemento_buscado=500;
    srand(time(NULL));
    int i,opcion,posicion_del_valor=rand()%1000;
    int arreglo[n];
    for ( i = 0; i < n; i++) {
        if (i == posicion_del_valor) {
            arreglo[i]=elemento_buscado;
        } else {
            arreglo[i]=rand()%1000;
        }
    }
    printf("Ordenar arreglo por:\n1. Quicksort\n2. Bubblesort\n");
    scanf("%d", &opcion);
    if(opcion==1){
      quicksort(arreglo,0,n,n/2);
    }
    else if(opcion==2){
      bubblesort(arreglo,n);
    }
    else{
      printf("Opcion Incorrecta");
      return 0;
    }
    printf("El vector ordenado es:\n[ ");
    for( i = 0; i < n; i++){
        printf("%d ",arreglo[i]);
    }
    printf("]\n");
    busqueda_binaria(arreglo,0,n-1,(n-1)/2,elemento_buscado);
    printf("La posiccion del elemento buscado es: %d\n", posicion_elemento_buscado);
    return 0;
}
int busqueda_binaria(int *arreglo, int lim_inf, int lim_sup, int posicion_piv, int elemento_buscado){
    while(lim_inf <= lim_sup && posicion_elemento_buscado != posicion_piv){
        if(elemento_buscado==arreglo[posicion_piv]){
            posicion_elemento_buscado=posicion_piv;
        }
        else if(elemento_buscado<arreglo[posicion_piv]){
			      lim_sup=posicion_piv-1;
            posicion_piv=((lim_inf+lim_sup)/2);
            //printf("%d  %d  %d\n", lim_inf,lim_sup,posicion_piv);
            busqueda_binaria(arreglo,lim_inf,lim_sup,posicion_piv,elemento_buscado);
		    }
		    else if(elemento_buscado>arreglo[posicion_piv]){
			      lim_inf=posicion_piv+1;
			      posicion_piv=((lim_inf+lim_sup)/2);
            //printf("%d  %d  %d\n", lim_inf,lim_sup,posicion_piv);
			      busqueda_binaria(arreglo,lim_inf,lim_sup,posicion_piv,elemento_buscado);
		    }
	  }
    if(lim_inf > lim_sup){
		    printf("El valor buscado no esta en el arreglo\n");
		    exit(1);
	  }
	  return 0;
}
void bubblesort(int arreglo[],int tamano) {
    int pasadas,j,aux;
    for ( pasadas = 0; pasadas < (tamano-1); pasadas++) {
        for ( j = 0; j < (tamano-1); j++) {
            if (arreglo[j] > arreglo[j+1]) {
                aux=arreglo[j];
                arreglo[j]=arreglo[j+1];
                arreglo[j+1]=aux;
            }
        }
    }
}

void quicksort(int *arreglo, int i_izq, int i_der, int posicion_piv){
    int i,valor_menor;
	  guardar_valor=i_izq;
	  valor_pivote=arreglo[posicion_piv];
	  if( i_izq < i_der){
		    for( i = i_izq; i <= i_der; i++){
			      if(arreglo[i] < valor_pivote){
                valor_menor=arreglo[i];
				        arreglo[i]=arreglo[guardar_valor];
				        arreglo[guardar_valor]=valor_menor;
				        guardar_valor+=1;
			      }
		    }
		    if(valor_pivote == arreglo[posicion_piv]){
            valor_menor=arreglo[guardar_valor];
			      arreglo[guardar_valor]=arreglo[posicion_piv];
			      arreglo[posicion_piv]=valor_menor;
		    }
		    quicksort(arreglo,i_izq,guardar_valor-1,(i_izq+guardar_valor-1)/2);
		    quicksort(arreglo,guardar_valor+1,i_der,(i_der+guardar_valor+1)/2);
	  }
}
