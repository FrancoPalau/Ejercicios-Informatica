/*Implementar el ejercicio 28 utilizando estructuras de datos dinámicas (arreglos con tamaño definido en
tiempo de ejecución para la matriz del mapa).
Consideraciones:
1. Utilice la función calloc()
2. Recuerde que para arreglos de N dimensiones, la memoria debe reservarse con calloc() de manera
independiente para cada dimensión*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define  COUNT 10
int main() {
  char lectura[80];
  int inicioX,inicioY,finX,finY;
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
  int **arreglo;
	arreglo=(int**)calloc(filas,sizeof(int*));
	for(i=0;i<filas;i++){
		arreglo[i]=(int*)calloc(columnas,sizeof(int));
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
          i=0;
          while(lectura[i]!=')'){
            if(lectura[i]==','){
              inicioX=(int)(lectura[i-1]-48);
              inicioY=(int)(lectura[i+1]-48);
            }
            i++;
          }
          continue;
        }
        //Si lee la palabra fin, busca hasta la coma y almacena los valores antes y despues de la coma
        else if (lectura[0]=='f' && lectura[1]=='i' && lectura[2]=='n'){
          i=0;
          while(lectura[i]!=')'){
    				if(lectura[i]==','){
    					finX=(int)(lectura[i-1]-48);
    					finY=(int)(lectura[i+1]-48);
    				}
            i++;
    			}
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
    //Impresion de la MATRIZ
    for ( i = 0; i < filas; i++) {
        for ( j = 0; j < columnas; j++) {
            printf("%d ", arreglo[i][j]);
        }
        printf("\n" );
    }
  	fclose(fp);
    for(i = 0; i < columnas; i++){
        free(arreglo[i]);
    }
    free(arreglo);

  return 0;
}
