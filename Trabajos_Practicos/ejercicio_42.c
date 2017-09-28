/*Implementar el ejercicio 41 mediante multiprocessing. En este caso se creará un proceso por cada fila
de la matriz resultado. La matriz debe generarse antes de crear los procesos hijos de manera que cada
hijo tenga una copia de la matriz. Cada proceso hijo, al terminar su trabajo, debe enviar la fila resultante
al padre a través de un pipe. Utilice semáforos al momento de enviar los datos al padre. Imprima el
resultado por pantalla.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <bits/signum.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <time.h>
//Defines
#define ID_SEMAFORO "semaforo"
#define ENTRADA_PIPE 0
#define SALIDA_PIPE 1
//Variables globales
int **matrix1,**matrix2,**matrix3;
int f1,c1,f2,c2;
int contador2;
sem_t* semaforo;
//Firmas de funciones
void calcula_fila(int i, int extremo_tuberia);
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
        //Crea la tuberia
        int tuberia[2];
        pipe(tuberia);
        int contador=0;
        //Empieza la creacion de los hijos
        pid_t pid_hijo;
        do {
            contador++;
            pid_hijo=fork();

            if (pid_hijo == -1) {
              printf("Error");
              exit(1);
            }
            else if (pid_hijo == 0) {
                //Accion del hijo
                //printf("Soy el hijo %d\n",contador-1);
                close(tuberia[ENTRADA_PIPE]);
                calcula_fila(contador-1,tuberia[SALIDA_PIPE]);
            }
        } while(pid_hijo!=0 && contador<f1);
        //Accion del padre
        if (pid_hijo != 0) {
            int fila[c2];
            int status;
            close(tuberia[SALIDA_PIPE]);
            semaforo = sem_open(ID_SEMAFORO, O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, 1);
            printf("La matriz resultado es: \n" );
            //Leemos todas las filas, las colocamos en la matrix3 e imprimimos
            for ( i =f1-1; i >=0; i--) {
                waitpid(pid_hijo,&status,0);
                read(tuberia[ENTRADA_PIPE],fila,sizeof(fila));
                for ( j = 0; j < c2; j++) {
                    matrix3[i][j]=fila[j];
                    printf("%d ",matrix3[i][j] );
                }
                printf("\n" );
            }
            //Termina los procesos hijos
            for( i = 0; i < f1; i++){
        			kill(pid_hijo, SIGTERM);
        		}
            //Cerramos el descriptor del pipe abierto
						close(tuberia[ENTRADA_PIPE]);
            //Cerramos el semaforo
            sem_close(semaforo);
            //Le indicamos al kernel de linux que el semaforo ya no se usa.
            sem_unlink(ID_SEMAFORO);
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
    }
    return 0;
}
//Funcion que recibe la cantidad de filas de la matriz final y el extremo donde
//se escribe el resultado, calcula la fila y luego la escribe en el pipe
void calcula_fila(int f1, int extremo_tuberia){
    //static int contador2;
    int j,k;
    int fila[c2];
    //Creacion de semaforo para coordinar la entrega de la fila
    semaforo=sem_open(ID_SEMAFORO, O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, 1);
    //Calculo de la fila
    for ( j = 0; j < c2; j++) {
        fila[j]=0;
        for ( k = 0; k < c1; k++) {
            fila[j]=fila[j]+(matrix1[f1][k]*matrix2[k][j]);
        }
    }
    //contador2++;
    //Down sobre el semaforo para la escritura
    sem_wait(semaforo);
    //Enviamos la fila al padre
    write(extremo_tuberia,fila,sizeof(fila));
    //Up al semaforo
    sem_post(semaforo);
}
