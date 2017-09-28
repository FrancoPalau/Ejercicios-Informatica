/*Implemente una biblioteca con funciones para manipulación de listas doblemente enlazadas. Cree un
nodo para la lista mediante struct (el contenido de cada nodo es a libre elección del alumno), e
implemente funciones para
1. agregar un elemento a la lista,
2. eliminar un elemento de la lista,
3. modificar un elemento de la lista
4. mostrar todos los elementos de la lista.*/

typedef struct nodo{
        int dato;
        struct nodo *siguiente;
        struct nodo *anterior;
}NODO;

NODO *primero=NULL;
NODO *ultimo=NULL;

//Esta funcion agrega un nodo al principio de la lista
int agregar_principio();

//Esta funcion agrega un nodo al final de la lista
int agregar_final();

//Esta funcion agrega un nodo a la lista despues del que se le dio como parametro
int agrega_despues_de(NODO *actual);

//Esta funcion muestra los datos de cada nodo de la lista
int mostrar_datos();

//Esta funcion elimina el nodo que tiene el dato buscado
int eliminar_nodo();

//Esta funcion busca el nodo en donde esta el dato que se quiere modificar y lo cambia
int buscar_nodo();

//Esta funcion elimina la lista completa
int borrar_lista();
