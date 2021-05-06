#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Tarea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}Tarea;

typedef struct Nodo{
    Tarea T;
    Nodo *Siguiente;
}Nodo;


Nodo * crearListaVacia();
void insertarNodo(Nodo **lista, Nodo *nodo);
void cargarTareas(Nodo **lista, int cantidad);
void mostrarTarea(Nodo *lista);
void moverTareas(Nodo **listaP, Nodo **listaR, int cantidad);
void BusquedaPorPalabra(Nodo **lista, char *palabraClave, int cantidad);
void BusquedaPorID(Nodo **lista, int idBuscado, int cantidad);

//----------------------------------------------------------------

int main()
{
    srand(time(NULL));
    int cantTareas, idBuscado, contador;
    Nodo *Start, *nodoRealizadas, *aux;
    char palabraClave[20];

    //crear Nodos vacios
    Start = crearListaVacia();
    nodoRealizadas = crearListaVacia();

    //cargar nodo de tareas
    printf("\n Ingrese la cantidad de tareas (max 5): ");
    scanf("%d", &cantTareas);
    cargarTareas(&Start, cantTareas);

    //----------------------------------------------------------------
    /*
    printf("\n___________________________________________\n");
    printf("\n BUSQUEDA DE TAREAS: \n");

    //por palabra
    fflush(stdin);
    printf("\n 1) Ingrese la palabra clave para buscar tarea: ");
    gets(palabraClave);
    BusquedaPorPalabra(arregloTareas, palabraClave, cantTareas);

    //por id
    printf("\n\n 2) Ingrese el ID de la tarea que desea buscar (de 0 a %d): ", cantTareas - 1);
    scanf("%d", &idBuscado);
    BusquedaPorID(arregloTareas, idBuscado, cantTareas);
    */

    //----------------------------------------------------------------

    //marcar tareas como realizadas y mostrar
    printf("\n___________________________________________\n");
    printf("\n CHEQUEO DE TAREAS: \n");
    moverTareas(&Start, &nodoRealizadas, cantTareas);

    printf("\n___________________________________________\n");
    printf("\n TAREAS PENDIENTES: ");
    aux = Start;
    while (aux !=NULL){
        mostrarTarea(aux);
        aux = aux->Siguiente;
        contador++;
    }
    if (contador == 0){
        printf("No hay tareas pendientes.");
    }
    
    

    printf("\n___________________________________________\n");
    printf("\n TAREAS REALIZADAS: ");
    aux = nodoRealizadas;
    contador = 0;
    while (aux !=NULL){
        mostrarTarea(aux);
        aux = aux->Siguiente;
        contador++;
    }
    if (contador == 0){
        printf("No hay tareas realizadas.");
    }



    return 0;
}


//----------------------------------------------------------------

Nodo * crearListaVacia()
{
    return NULL;
}


void cargarTareas(Nodo **lista, int cantidad)
{
    Nodo *nuevoNodo;
    for (int i = 0; i < cantidad; i++)
    {
        nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
        nuevoNodo->Siguiente = NULL;

        nuevoNodo->T.TareaID = i;
        nuevoNodo->T.Descripcion = (char*)malloc(sizeof(char)*50);
        fflush(stdin);
        printf("\nIngrese la descripcion de la tarea %d: ",i);
        gets(nuevoNodo->T.Descripcion);
        nuevoNodo->T.Duracion = 10 + rand()% 90;
        
        insertarNodo(lista, nuevoNodo);
    }
    
}

void insertarNodo(Nodo **lista, Nodo *nodo)
{
    Nodo * aux = *lista;
    if(aux != NULL){
        while(aux->Siguiente != NULL){
            aux = aux->Siguiente;
        }
        aux->Siguiente = nodo;
    }else{
        *lista = nodo;
    }

}


void mostrarTarea(Nodo *lista)
{

    printf("\n#### TAREA NUMERO %d ####\n", lista->T.TareaID + 1);
    printf("\nID: %d", lista->T.TareaID);
    printf("\nDescripcion: %s", lista->T.Descripcion);
    printf("\nDuracion: %d", lista->T.Duracion);
    printf("\n");
}


void moverTareas(Nodo **listaP, Nodo **listaR, int cantidad)
{
    char respuesta[5];
    Nodo * aux = *listaP; //pendientes
    Nodo * aux2 = *listaR; //realizados
    Nodo * anterior = aux;

    while (aux != NULL)
    {
        mostrarTarea(aux);
        printf("\n---------------------");
        fflush(stdin);
        printf("\nLa tarea fue realizada? (s/n): \n");
        gets(respuesta);

        if (respuesta[0] == 's' || respuesta[0] == 'S')
        {
            aux2 = aux;
            aux = aux2->Siguiente;

            if (anterior->Siguiente == aux)
            {
                *listaP = aux;
                anterior = aux;
            }else{
                anterior->Siguiente = aux;
            }
            
            aux2->Siguiente = *listaR;
            *listaR = aux2;

        }else{
            anterior = aux;
            aux = aux->Siguiente;
        }
    }
}


void BusquedaPorPalabra(Nodo **lista, char *palabraClave, int cantidad)
{
    int contador=0;
    Nodo *aux = *lista;

    printf("\nTarea(s) encontrada(s): \n");
    for (int i = 0; i < cantidad; i++)
    {
        if((strstr((aux->T.Descripcion), palabraClave)) != NULL)
        {
            mostrarTarea(aux);
            contador++;
        }
    }

    if (contador == 0)
        {
            printf("No se encontraron coincidencias.");
        }
}


void BusquedaPorID(Nodo **lista, int idBuscado, int cantidad)
{
    printf("\nTarea encontrada: \n");
    int contador = 0;
    Nodo *aux = *lista;
    for (int i = 0; i < cantidad; i++)
    {
        if ((aux->T.TareaID) == idBuscado)
        {
            mostrarTarea(aux);
            contador++;
        }
        
    }
    if (contador == 0)
    {
        printf("No se encontraron coincidencias.");
    }
    
}