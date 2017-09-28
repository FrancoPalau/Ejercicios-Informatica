/*
 * ejercicio_43.c
 *
 *  Created on: 04/11/2016
 *      Author: root
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 	//Funciones sleep
#include <pthread.h>	//Threads
#include <hidapi.h>		//USB-HID

typedef int boolean;
#define TRUE 1
#define FALSE 0
boolean en_ejecucion;
//int p[2];
int menor[2];
int mayor[2];
int valor[2];

void *captura_finalizacion(void *arg){
	getchar(); //Este extrae del buffer del teclado el ENTER que quedo de la seleccion del usuario
	getchar(); //Este captura realmente el nuevo ENTER que el usuario presiona para terminar la ejecucion
	en_ejecucion=FALSE;
	return NULL;
}

//Muestra el contenido del buffer de manera "raw" (cruda). Muestra los valores leidos del dispositivo, byte por byte, en sistema decimal
void despliega_salida_cruda(unsigned char buffer[], int LONGITUD_BUFFER){
	int i;
	for(i = 0; i < LONGITUD_BUFFER; i++){
		//Relleno para que todos los numeros muestren 3 cifras
		if(buffer[i] < 100)
			printf("0");
		if(buffer[i] < 10)
			printf("0");

		//Mostramos el valor leido
		printf("%d ", buffer[i]);
	}
	printf("\n");
}
//Muestra el contenido del buffer de manera procesada, agregando semantica a cada grupo de bytes/bits
void despliega_salida_mouse(unsigned char buffer[]){

    valor[0]=valor[0]+/*(-1)**/(int)((char)buffer[2]);
    valor[1]=valor[1]+/*(-1)**/(int)((char)buffer[3]);
    if(valor[0]<menor[0]){
        valor[0]=menor[0];
    }
    if(valor[1]<menor[1]){
        valor[1]=menor[1];
    }
    if(valor[0]>mayor[0]){
        valor[0]=mayor[0];
    }
    if (valor[1]>mayor[1]){
        valor[1]=mayor[1];
    }

	printf("Boton izquierdo: %s\n", (buffer[1]==1)?"Presionado":"Libre");
	printf("Boton derecho: %s\n", (buffer[1]==2)?"Presionado":"Libre");
	printf("Boton de la ruedita: %s\n", (buffer[1]==4)?"Presionado":"Libre");
	printf("Variacion de (x,y): [%d,%d]\n",(char)buffer[2],(char)buffer[3]);
	printf("Posicion en pixeles(x,y): [%d,%d]\n",valor[0],valor[1]);
	printf("Movimiento de la rueda: %s\n", buffer[4]==1?"Arriba":buffer[4]==255?"Abajo":"Nulo");

}

int main(int argc, char* argv[]){
	struct hid_device_info *dispositivos_disponibles, *dispositivo_actual;
	//p[0]=0;
	//p[1]=0;
	menor[0]=0;
	menor[1]=0;
	valor[0]=500;
	valor[1]=500;
	mayor[0]=1366;
	mayor[1]=768;
	//Listamos los dispositivos USB-HID conectados (los argumentos en 0 indican que se listen todos, sin filtro por vendor_id o product_id)
	dispositivos_disponibles = hid_enumerate(0x0, 0x0);
	dispositivo_actual = dispositivos_disponibles;
	printf("\nDispositivos encontrados:\n========================\n");
	int i=1;
	while(dispositivo_actual) {
		printf("%d. Vendor Id   : %04hx\n", i, dispositivo_actual->vendor_id);
		printf("   Product Id  : %04hx\n", dispositivo_actual->product_id);
		printf("   Path        : %s\n",  dispositivo_actual->path);
		printf("   No. de serie: %ls\n", dispositivo_actual->serial_number);
		printf("   Fabricante  : %ls\n", dispositivo_actual->manufacturer_string);
		printf("   Producto    : %ls\n", dispositivo_actual->product_string);
		printf("   Release     : %hx\n", dispositivo_actual->release_number);
		printf("   Interfaz    : %d\n",  dispositivo_actual->interface_number);
		printf("\n");
		dispositivo_actual = dispositivo_actual->next;
		i++;
	}

	//Permitimos al usuario seleccionar el dispositivo a muestrear
	int cantidad_dispositivos = i-1;
	int opcion;
	printf("Elija el dispositivo a monitorear (0 = SALIR): ");
	scanf("%d", &opcion);
	while(opcion < 0 || opcion > cantidad_dispositivos){
		printf("Opción invalida! Elija una opción entre 0 y %d", cantidad_dispositivos);
		scanf("%d", &opcion);
	}

	if(opcion != 0){
		//Buscamos el dispositivo elegido por el usuario
		dispositivo_actual = dispositivos_disponibles;
		for(i = 1; i < opcion; i++){
			if(dispositivo_actual->next)
				dispositivo_actual = dispositivo_actual->next;
		}

		//Abrimos el dispositivo
		hid_device *dispositivo;
		dispositivo = hid_open(dispositivo_actual->vendor_id, dispositivo_actual->product_id, NULL);

		//Lanzamos un thread para capturar la senal de finalizacion (cuando el usuario presiona ENTER)
		pthread_t tid;
		pthread_create(&tid, NULL, captura_finalizacion, NULL);

		//Creamos el buffer
		const int LONGITUD_BUFFER = 5;
		unsigned char buffer[LONGITUD_BUFFER];

		//Leemos la entrada cada 100 ms
		en_ejecucion = TRUE;
		while(en_ejecucion == TRUE){
			//Limpiamos la pantalla (esto no es estandar, depende de cada SO)
			printf("\033[2J");

			//Esperamos 100 ms
			usleep(10000);

			//Leemos del dispositivo
			memset(buffer, 0, sizeof(buffer)); //limpiamos el buffer
			hid_read(dispositivo, buffer, sizeof(buffer));

			//Mostramos por pantalla
			despliega_salida_cruda(buffer, LONGITUD_BUFFER);
			despliega_salida_mouse(buffer);
		}

		pthread_join(tid, NULL);

		//Al salir, cerramos el dispositivo
		hid_close(dispositivo);
	}

	//Liberamos la memoria utilizada por la lista de dispositivos disponibles
	hid_free_enumeration(dispositivos_disponibles);

	//Liberamos otras estructuras de datos internas de la biblioteca hidapi
	hid_exit();

	printf("\n\nEjecución terminada. Bye!\n");
	return 0;
}

