/*
 * ejercicio_44.c
 *
 *  Created on: 06/11/2016
 *      Author: root
 */
/*Mediante sockets TCP/IP implemente el ejercicio 43 con 2 procesos: uno (el cliente) lee los valores del
mouse y se lo envía al otro (servidor); el servidor muestra por pantalla la representación de los valores.
Los procesos pueden correr en la misma máquina o en máquinas remotas (esto es opcional).
Nota: En caso de correr en el mismo host, se pueden configurar los sockets del cliente y del servidor
con la IP del host, o bien con la IP 127.0.0.1 que representa el host local (loopback).*/
#include <sys/socket.h>		//Sockets
#include <arpa/inet.h>		//Sockets
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 	 	//Biblioteca para multiprocessing (fork)
#include <signal.h> 		//Biblioteca para enviar senales a los procesos (kill)
#include <bits/signum.h> 	//Biblioteca conconstantes para los tipos de senales
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>	//Threads
#include <hidapi.h>	//USB-HID

typedef int boolean;
#define TRUE 1
#define FALSE 0
boolean en_ejecucion;

#define PUERTO_SERVER 3333
#define MAX_LARGO_COLA 100

#define SERVER 0
#define CLIENTE 1

int rolProceso;
int menor[2];
int mayor[2];
int valor[2];

//Firmas
void *cliente(void *arg);
void servidor();
void despliega_salida_cruda(/*unsigned*/ char buffer[], int LONGITUD_BUFFER);
void despliega_salida_mouse(/*unsigned*/ char buffer[]);
//void *captura_finalizacion(void *arg);
void manejador_signals(int signal_type);

int main(int argc, char* argv[]) {
    pid_t pid_servidor;
	 menor[0]=0;
	 menor[1]=0;
	 valor[0]=500;
	 valor[1]=500;
	 mayor[0]=1366;
	 mayor[1]=768;
    //Inicializacion
    en_ejecucion=TRUE;

    //Registramos con el kernel la funcion que maneja las signals
    signal(SIGINT, manejador_signals);
    signal(SIGTERM, manejador_signals);

    pthread_t tid;

    pid_servidor = fork();
    if(pid_servidor == -1){
      printf("Error al iniciar servidor");
      return 1;
    }
    else if(pid_servidor == 0){
      servidor();
    }
    else if(pid_servidor != 0){

    	pthread_create(&tid, NULL, cliente, NULL);
        //cliente();
      }
      //else{
        getchar();
        getchar();

        //kill(pid_servidor, SIGTERM);
        //kill(pid_cliente, SIGTERM);

        //int status;
        //waitpid(pid_servidor, &status, 0);
        //waitpid(pid_cliente, &status, 0);

        pthread_join(tid, NULL);
        kill(pid_servidor, SIGTERM);
        printf("\nEjecución terminada. Bye\n");
      //}


  return 0;
}
//Funcion que ejecuta el proceso cliente
void *cliente(void *arg){
	 int sd; //socket descriptor

	 rolProceso = CLIENTE;

	  //Creamos el socket:
	  //	AF_INET: Familia de protocolos TCP/IP
    //	SOCK_STREAM: Servicio orientado a la conexion (normalmente protocolo TCP)
	  sd = socket(AF_INET, SOCK_STREAM, 0);
    if(sd < 0){
		    perror("Error al crear socket (cliente)");
        abort();
      }

	   //Creamos la configuracion de direccion para el socket
	   struct sockaddr_in direccionSocket; 						//Estructura para configurar el socket
    memset(&direccionSocket, 0, sizeof(direccionSocket)); 		//Utilizamos memset para inicializar a 0 todos los bytes de la estructura de configuracion del socket
    direccionSocket.sin_family = AF_INET; 						//Familia de direcciones de TCP/IP
    inet_aton("127.0.0.1", &(direccionSocket.sin_addr));		//Especificamos la direccion IP al que se conectara el socket, y la convertimos al formato de la red
    direccionSocket.sin_port = htons(PUERTO_SERVER);       		//Especificamos el puerto TCP al que se conectara el socket, y lo convertimos al byte order de la red

    //Establecemos conexion con el server
    int conectado;
    	do{
    		sleep(1);
    		conectado = connect(sd, (struct sockaddr *)&direccionSocket,sizeof(direccionSocket));
    	}while(conectado < 0);

      //ACA IRIA LA PARTE DE LEER LOS DATOS DEL USB
      struct hid_device_info *dispositivos_disponibles, *dispositivo_actual;

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
      printf("Cliente: 1\n");

      if(opcion != 0){
        //Buscamos el dispositivo elegido por el usuario
        dispositivo_actual = dispositivos_disponibles;
        for(i = 1; i < opcion; i++){
          if(dispositivo_actual->next)
            dispositivo_actual = dispositivo_actual->next;
        }


      //Abrimos el dispositivo
        printf("Cliente: 2\n");
      hid_device *dispositivo;
      dispositivo = hid_open(dispositivo_actual->vendor_id, dispositivo_actual->product_id, NULL);
      printf("Cliente: 3\n");

      //Lanzamos un thread para capturar la senal de finalizacion (cuando el usuario presiona ENTER)
      //pthread_t tid;
      //pthread_create(&tid, NULL, captura_finalizacion, NULL);

      //Creamos el buffer
      const int LONGITUD_BUFFER = 5;
      unsigned char buffer[LONGITUD_BUFFER];

      //Leemos la entrada cada 100 ms
      en_ejecucion = TRUE;
      printf("Cliente: 4\n");
      while(en_ejecucion == TRUE){
          printf("Cliente: 5\n");
        //Limpiamos la pantalla (esto no es estandar, depende de cada SO)
        printf("\033[2J");

        //Esperamos 100 ms
        usleep(10000);

        //Leemos del dispositivo
        memset(buffer, 0, sizeof(buffer)); //limpiamos el buffer
        printf("Cliente: 6\n");
        hid_read(dispositivo, buffer, sizeof(buffer));
        printf("Cliente: 7\n");

        //Enviamos buffer al servidor
        printf("Cliente: Enviando\n");
        send(sd, buffer, sizeof(buffer), 0);
        printf("Cliente: Enviado\n");

      }
        //pthread_join(tid, NULL);

  		//Al salir, cerramos el dispositivo
  		hid_close(dispositivo);
  	}

  	//Liberamos la memoria utilizada por la lista de dispositivos disponibles
  	hid_free_enumeration(dispositivos_disponibles);

  	//Liberamos otras estructuras de datos internas de la biblioteca hidapi
  	hid_exit();

  	printf("\n\nEjecución terminada. Bye!\n");

	close(sd);
	return NULL;
}
//Funcion que ejecuta el proceso servidor
void servidor(){
	 int sd; //socket descriptor

	  rolProceso = SERVER;

	  //Creamos el socket:
	  //	AF_INET: Familia de protocolos TCP/IP
	  //	SOCK_STREAM: Servicio orientado a la conexion (normalmente protocolo TCP)
	  sd = socket(AF_INET, SOCK_STREAM, 0);
	  if(sd < 0){
		  perror("Error al crear socket (servidor)");
		  abort();
	  }

	  //Creamos la configuracion de direccion para el socket
	  struct sockaddr_in direccionSocket; 						//Estructura para configurar el socket
	  memset(&direccionSocket, 0, sizeof(direccionSocket)); 		//Utilizamos memset para inicializar a 0 todos los bytes de la estructura de configuracion del socket
	  direccionSocket.sin_family = AF_INET; 						//Familia de direcciones de TCP/IP
	  inet_aton("127.0.0.1", &(direccionSocket.sin_addr));		//Especificamos la direccion IP al que se conectara el socket, y la convertimos al formato de la red
	  direccionSocket.sin_port = htons(PUERTO_SERVER);       		//Especificamos el puerto TCP al que se conectara el socket, y lo convertimos al byte order de la red

	   //Enlazamos el socket con la direccion local
	    if(bind(sd, (struct sockaddr *)&direccionSocket,sizeof(direccionSocket)) < 0){
		    perror("Error al enlazar socket al puerto (servidor)");
		    abort();
	    }

	  //Configuramos el socket para que escuche conexiones, y configuramos una cantidad maxima MAX_LARGO_COLA de conexiones que podemos poner en la cola
	  listen(sd, MAX_LARGO_COLA);

	  //Creamos las variables requeridas para esperar una conexion
	  struct sockaddr_in direccionSocketCliente;
	  socklen_t longitudDireccionCliente;
	  int sd_aceptado;  //socket creado automaticamente cuando se acepta una conexion

	  //El proceso se bloquea esperando una conexion
	  sd_aceptado = accept(sd, (struct sockaddr *)&direccionSocketCliente, &longitudDireccionCliente);

	  char buffer_lectura[5];
      en_ejecucion = TRUE;
	  while(en_ejecucion){
		printf("Server: Leyendo\n");
		//Ahora intentamos leer los bytes transferidos. El proceso se bloquea si no hay nada que leer
		recv(sd_aceptado, buffer_lectura, sizeof(buffer_lectura), 0);
		printf("Server: Leido\n");
		despliega_salida_cruda(buffer_lectura, 5);
        despliega_salida_mouse(buffer_lectura);
	  }

	//Cerramos el nuevo socket creado con accept
	close(sd_aceptado);

	//Cerramos el socket original
	close(sd);
}
//Muestra el contenido del buffer de manera "raw" (cruda). Muestra los valores leidos del dispositivo, byte por byte, en sistema decimal
void despliega_salida_cruda(/*unsigned*/ char buffer[], int LONGITUD_BUFFER){
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
void despliega_salida_mouse(/*unsigned*/ char buffer[]){

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
		printf("Movimiento de la rueda: %s\n", buffer[4]==1?"Arriba":buffer[4]==-1?"Abajo":"Nulo");
}
/*void *captura_finalizacion(void *arg){
	getchar(); //Este extrae del buffer del teclado el ENTER que quedo de la seleccion del usuario
	getchar(); //Este captura realmente el nuevo ENTER que el usuario presiona para terminar la ejecucion
	en_ejecucion=FALSE;
	return NULL;
}*/
//Esta funcion maneja las señales que recibe del kernel ("interrupciones de software")
void manejador_signals(int signal_type)
{
  char rolProceso[10];
  if(rolProceso == SERVER)
	  strcpy(rolProceso, "Servidor");
  else
	  strcpy(rolProceso, "Cliente");

  if (signal_type == SIGTERM){
	  en_ejecucion = FALSE;
	  printf("%s: Señal SIGTERM recibida. Terminando proceso.\n", rolProceso);
  }
  else if (signal_type == SIGKILL){
	  en_ejecucion = FALSE;
	  printf("%s: Señal SIGKILL recibida. Terminando proceso.\n", rolProceso);
  }
  else
	printf("Señal desconocida. Ignorando...\n\n");
}

