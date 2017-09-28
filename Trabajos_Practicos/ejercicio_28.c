#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define  COUNT 10
int x,y;
int leer_coordenadas(char lectura[],char aux1[],char aux2[]);
int main() {
  char lectura[80];
  char aux1[20];
  char aux2[20];
  char aux3[20];
  char aux4[20];
  char aux[2];
  int arreglo[10][10];
  int inicioX,inicioY,finX,finY;
  int i,k,j=0;
  FILE *fp;
  fp = fopen ("leer_28.txt","r");
  if (fp==NULL){
		printf("\nError de apertura del archivo. \n\n");
    }
  else{
    while(feof(fp) == 0){ //Lee hasta que no encuentre el fin del archivo
        fscanf(fp," %[^\n]",lectura);//Lee hasta que encuentra el caracter de fin de linea
  		  if(lectura[0]=='#'){//Si lee un comentario lo omite
  			     continue;
  		  }
        //Si lee la palabra inicio, busca hasta la coma y almacena los valores antes y despues de la coma
        else if (lectura[0]=='i' && lectura[1]=='n' && lectura[2]=='i' && lectura[3]=='c' && lectura[4]=='i' && lectura[5]=='o'){
          leer_coordenadas(lectura,aux1,aux2);
          inicioX=x;
          inicioY=y;
          continue;
        }
        //Si lee la palabra fin, busca hasta la coma y almacena los valores antes y despues de la coma
        else if (lectura[0]=='f' && lectura[1]=='i' && lectura[2]=='n'){
          leer_coordenadas(lectura,aux3,aux4);
          finX=x;
          finY=y;
    			continue;
    		}
        for(k=0;k<10;k++){
          aux[0]=lectura[k];
    			arreglo[j][k]=atoi(aux);
    		}
    		j++;
    }
    //Impresion de las variables
    printf("\n inicioX:%d\n inicioY:%d\n finX:%d\n finY:%d\n",inicioX,inicioY,finX,finY);
    //Impresion de la MATRIZ
    for ( i = 0; i < 10; i++) {
        for ( j = 0; j < 10; j++) {
            printf("%d ", arreglo[i][j]);
        }
        printf("\n" );
    }
  	fclose(fp);
  }
  return 0;
}
int leer_coordenadas(char lectura[],char aux1[],char aux2[]){
  int i,k;
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
        aux1[k]='\0';
        k=0;
        i++;
        while (lectura[i]!=')') {
          aux2[k]=lectura[i];
          k++;
          i++;
        }
        aux2[k]='\0';
    }
    i++;
  }
  x=atoi(aux1);
  y=atoi(aux2);
  /*for ( i = 0; i < 20; i++) {
      aux1[i]=0;
      aux2[i]=0;
  }*/
  return 0;
}
