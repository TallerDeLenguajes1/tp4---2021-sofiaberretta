#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Tarea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}Tarea;

void cargarTareas(Tarea **arreglo, int cantidad);
void mostrarTarea(Tarea *arreglo);
void moverTareas(Tarea **pendientes, Tarea **realizadas, int cantidad);
void BusquedaPorPalabra(Tarea **arreglo, char *palabraClave, int cantidad);
void BusquedaPorID(Tarea **arreglo, int idBuscado, int cantidad);

//----------------------------------------------------------------

int main()
{
    srand(time(NULL));
    int cantTareas, idBuscado;
    Tarea **arregloTareas, **arregloRealizadas;
    char palabraClave[20];

    //crear tareas
    printf("\n Ingrese la cantidad de tareas (max 5): ");
    scanf("%d", &cantTareas);
    arregloTareas = (Tarea**)malloc(sizeof(Tarea*)*cantTareas);
    cargarTareas(arregloTareas, cantTareas);

    //----------------------------------------------------------------

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


    //----------------------------------------------------------------

    //marcar tareas como realizadas y mostrar
    arregloRealizadas = (Tarea**)malloc(sizeof(Tarea*)*cantTareas);
    printf("\n___________________________________________\n");
    printf("\n CHEQUEO DE TAREAS: \n");
    moverTareas(arregloTareas, arregloRealizadas, cantTareas);

    printf("\n___________________________________________\n");
    printf("\n TAREAS PENDIENTES: ");
    for (int i = 0; i < cantTareas; i++)
    {
        if ((*(arregloTareas+i)) !=NULL)
        {
            mostrarTarea((*(arregloTareas+i)));
        }
    }

    printf("\n___________________________________________\n");
    printf("\n TAREAS REALIZADAS: ");
    for (int i = 0; i < cantTareas; i++)
    {
        if ((*(arregloRealizadas+i)) !=NULL)
        {
            mostrarTarea((*(arregloRealizadas+i)));
        }
        
    }

    return 0;
}


//----------------------------------------------------------------

void cargarTareas(Tarea **arreglo, int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        *(arreglo + i)= (Tarea*)malloc(sizeof(Tarea));
        (*(arreglo + i))->TareaID = i;

        (*(arreglo + i))->Descripcion = (char*)malloc(sizeof(char)*80);
        fflush(stdin);
        printf("\nIngrese la descripcion de la tarea %d: ",i);
        gets((*(arreglo + i))->Descripcion);

        (*(arreglo + i))->Duracion = 10 + rand()% 90;
        
    }
    
}


void mostrarTarea(Tarea *arreglo)
{

    printf("\n#### TAREA NUMERO %d ####\n", arreglo->TareaID + 1);
    printf("\nID: %d", arreglo->TareaID);
    printf("\nDescripcion: %s", arreglo->Descripcion);
    printf("\nDuracion: %d", arreglo->Duracion);
    printf("\n");
}


void moverTareas(Tarea **pendientes, Tarea **realizadas, int cantidad)
{
    char respuesta[5];
    for (int i = 0; i < cantidad; i++)
    {
        mostrarTarea((*(pendientes + i)));
        printf("\n---------------------");
        fflush(stdin);
        printf("\nLa tarea fue realizada? (s/n): \n");
        gets(respuesta);

        if (respuesta[0] == 's' || respuesta[0] == 'S')
        {
            (*(realizadas + i)) = (*(pendientes + i));
            (*(pendientes + i)) = NULL;

        }else{
            (*(realizadas + i)) = NULL;
        }
        
    }
    
}


void BusquedaPorPalabra(Tarea **arreglo, char *palabraClave, int cantidad)
{
    int contador=0;

    printf("\nTarea(s) encontrada(s): \n");
    for (int i = 0; i < cantidad; i++)
    {
        if((strstr((*(arreglo + i))->Descripcion, palabraClave)) != NULL)
        {
            mostrarTarea((*(arreglo + i)));
            contador++;
        }
    }

    if (contador == 0)
        {
            printf("No se encontraron coincidencias.");
        }
}


void BusquedaPorID(Tarea **arreglo, int idBuscado, int cantidad)
{
    printf("\nTarea encontrada: \n");
    int contador = 0;
    for (int i = 0; i < cantidad; i++)
    {
        if ((*(arreglo + i))->TareaID == idBuscado)
        {
            mostrarTarea((*(arreglo+i)));
            contador++;
        }
        
    }
    if (contador == 0)
    {
        printf("No se encontraron coincidencias.");
    }
    
}