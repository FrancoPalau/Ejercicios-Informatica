#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct nodo{
    int coordenada_x;
    int coordenada_y;
    struct nodo *anterior;
    struct nodo *siguiente;
}NODO;

int final=0;
int **arreglo;
int **copia_mapa;
int inicioX,inicioY,finX,finY,auxX,auxY;
//NODO *nuevo_elemento;
    NODO *primer_elemento;
    NODO *ultimo=NULL;
    NODO *nuevo_elemento;
int cant_nodos;

int recorre_mapa(int i, int j);
void mostrar_datos(NODO *primero);
int leer_coordenadas(char lectura[]);

int main() {
  char lectura[80];
  int i,k,j=0;
  int filas=0,columnas=0;
  FILE *fp;
  //Leemos una vez el archivo para saber las dimensiones del mapa
  fp = fopen ("leer_28.txt","r");
  if (fp==NULL){
		printf("\nError de apertura del archivo. \n\n");
    }
  else{
	  while(feof(fp)==0){
			fscanf(fp," %[^\n]",&lectura);//Lee hasta el fin de linea
			if(lectura[0]=='1' || lectura[0]=='0'){
				filas++;
				if(strlen(lectura)>columnas){
					columnas=strlen(lectura);
				}
			}
	  }
	  fclose(fp);
  }
  //Creamos la matriz dinamicamente
	arreglo=(int**)calloc(filas,sizeof(int*));
	for(i=0;i<filas;i++){
		arreglo[i]=(int*)calloc(columnas,sizeof(int));
	}
  //Creamos copia del mapa
  copia_mapa=(int**)calloc(filas,sizeof(int*));
  for(i=0;i<filas;i++){
    copia_mapa[i]=(int*)calloc(columnas,sizeof(int));
  }
  //Leemos otra vez el archivo, esta vez para almacenar los valores que se piden
  fp = fopen ("leer_28.txt","r");
  if (fp==NULL){
		printf("\nError de apertura del archivo. \n\n");
    }
  else{
    while(feof(fp) == 0){ //Lee hasta que no encuentre el fin del archivo
        fscanf(fp," %[^\n]",&lectura);//Lee hasta que encuentra el caracter de fin de linea
  		  if(lectura[0]=='#'){//Si lee un comentario lo omite
  			     continue;
  		  }
        //Si lee la palabra inicio, busca hasta la coma y almacena los valores antes y despues de la coma
        else if (lectura[0]=='i' && lectura[1]=='n' && lectura[2]=='i' && lectura[3]=='c' && lectura[4]=='i' && lectura[5]=='o'){
          leer_coordenadas(lectura);
          inicioX=auxX;
          inicioY=auxY;
          continue;
        }
        //Si lee la palabra fin, busca hasta la coma y almacena los valores antes y despues de la coma
        else if (lectura[0]=='f' && lectura[1]=='i' && lectura[2]=='n'){
          leer_coordenadas(lectura);
          finX=auxX;
          finY=auxY;
    			continue;
    		}
        //Guarda los valores del mapa en la matriz
        for(k=0;k<columnas;k++){
    			arreglo[j][k]=lectura[k]-48;
    		}
    		j++;
    }
  }
    //Impresion de las variables
    printf("\n inicioX:%d\n inicioY:%d\n finX:%d\n finY:%d\n",inicioX,inicioY,finX,finY);
    finX=1;
    finY=3;
    //Impresion de la MATRIZ
    for ( i = 0; i < filas; i++) {
        for ( j = 0; j < columnas; j++) {
            printf("%d ", arreglo[i][j]);
            copia_mapa[i][j]=arreglo[i][j];
        }
        printf("\n" );
    }
  	fclose(fp);
    //////////////////////////////////////////////////////////////////////////
    int estado;

    primer_elemento=(NODO*)malloc(sizeof(NODO));
    primer_elemento->coordenada_x=inicioX;
    primer_elemento->coordenada_y=inicioY;
    primer_elemento->siguiente=ultimo;
    primer_elemento->anterior=NULL;
    copia_mapa[primer_elemento->coordenada_x][primer_elemento->coordenada_y]=-1;
    cant_nodos=1;
    estado=recorre_mapa(primer_elemento->coordenada_x,primer_elemento->coordenada_y);
    if (estado==1) {
        printf("El camino a seguir es:\n" );
        mostrar_datos(primer_elemento);
        printf("Ha llegado al final\n" );
        /*NODO *aux;
        while (primer_elemento != NULL) {
            aux=primer_elemento->siguiente;
            free(primer_elemento);
            primer_elemento=aux;
        }*/

    }else if (estado==0) {
        printf("No existe camino\n");
        //mostrar_datos(primer_elemento);
        //free(primer_elemento);
        //cant_nodos--;
    }else{
        printf("Error en la funcion\n" );
    }
    printf("%d\n",cant_nodos );

    /*for(i = 0; i < filas; i++){
        free(arreglo[i]);
        free(copia_mapa[i]);
    }
    free(arreglo);
    free(copia_mapa);*/

  return 0;
}
int recorre_mapa(int i, int j) {
    int x,y,r;
    for ( x = i+1; x >= i-1; x--) {
        for ( y = j-1; y <= j+1; y++) {
            if (x>=0 && x<10 && y>=0 && x<10) {  //Verificacion para ver que no estemos accediendo a partes que no existen de la matriz
                if(copia_mapa[x][y]!=-1){ //Verificamos que no es un nodo leido
                    copia_mapa[x][y]=-1;
                    if (arreglo[x][y]==0) { //Verificamos que sea un nodo al que puedo ir
                        if (x!=i || y!=j) { //Verificamos que no me leo a mi mismo
                            if (x==finX && y==finY) { //Verificamos que llego a destino
                                //NODO *nuevo_elemento;
                                nuevo_elemento=(NODO*)malloc(sizeof(NODO));
                                nuevo_elemento->coordenada_x=x;
                                nuevo_elemento->coordenada_y=y;
                                ultimo->siguiente=nuevo_elemento;
                                nuevo_elemento->anterior=ultimo;
                                cant_nodos++;
                                return 1;
                            } else {
                                //NODO *nuevo_elemento;
                                nuevo_elemento=(NODO*)malloc(sizeof(NODO));
                                nuevo_elemento->coordenada_x=x;
                                nuevo_elemento->coordenada_y=y;
                                //actual->siguiente=nuevo_elemento;
                                ultimo->siguiente=nuevo_elemento;
                                nuevo_elemento->anterior=ultimo;
                                ultimo=nuevo_elemento;
                                cant_nodos++;
                                r=recorre_mapa(x,y);
                                if (r==1) {
                                    return 1;
                                }

                            }
                        }
                    }
                }
            }
        }
    }

    return 0;

}
void mostrar_datos(NODO *primero){
    NODO *actual;
    actual=(NODO*)malloc(sizeof(NODO));
    actual=primer_elemento;
    if (primero!= NULL) {
        while (actual != NULL) {
            printf("[%d ,",actual->coordenada_x);
            printf(" %d]\n",actual->coordenada_y );
            actual=actual->siguiente;
        }
    }else{
        printf("La lista esta vacia: \n" );
    }
}
int leer_coordenadas(char lectura[]){
  int i,k;
  char aux1[20];
  char aux2[20];
  i=0;
  while(lectura[i]!='\0'){
    if(lectura[i]=='('){
        k=0;
        i++;
        while (lectura[i]!=',') {
          aux1[k]=lectura[i];
          k++;
          i++;
        }
        k=0;
        i++;
        while (lectura[i]!=')') {
          aux2[k]=lectura[i];
          k++;
          i++;
        }
    }
    i++;
  }
  auxX=atoi(aux1);
  auxY=atoi(aux2);
  for ( i = 0; i < 20; i++) {
      aux1[i]=0;
      aux2[i]=0;
  }
  return 0;
}
