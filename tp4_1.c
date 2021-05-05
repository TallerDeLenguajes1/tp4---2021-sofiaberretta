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

int main()
{
    srand(time(NULL));
    int cantTareas;
    Tarea **arregloTareas, **arregloRealizadas;

    printf("\n Ingrese la cantidad de tareas (max 5): ");
    scanf("%d", &cantTareas);
    arregloTareas = (Tarea**)malloc(sizeof(Tarea*)*cantTareas);
    cargarTareas(arregloTareas, cantTareas);

    arregloRealizadas = (Tarea**)malloc(sizeof(Tarea*)*cantTareas);
    moverTareas(arregloTareas, arregloRealizadas, cantTareas);


}

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