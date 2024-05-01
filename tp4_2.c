#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

struct Tarea
{
    int TareaID;
    char *descripcion;
    int Duracion;
}typedef Tarea;

typedef struct Nodo
{
    Tarea T;
    struct Nodo *siguiente;
}Nodo;


Nodo* crearListaVacia();
Tarea cargarTarea(int id);
void agregarTareas(Nodo** Lista, int *id);
void mostrarLista(Nodo* Lista);
void transferirNodosPorId(Nodo **L1, Nodo **L2);
void mostrarTareaID(Nodo* L1, Nodo* L2);
void mostrarTareaPalabraClave(Nodo* L1, Nodo* L2);
void eliminarPrimerNodo(Nodo **L);


int main(){
    int id = 1000;
    int opcion;
    srand(time(NULL));
    Nodo *listaTareasPendientes = crearListaVacia();
    Nodo *listaTareasRealizadas = crearListaVacia();
    do
    {
        printf("\n\nQue operacion desea realizar?");
        printf("\n[0]. Agregar una nueva tarea a Pendientes");
        printf("\n[1]. Transferir tareas de la lista Pendientes a Realizadas");
        printf("\n[2]. Mostrar las listas");
        printf("\n[3]. Consultar tarea por id");
        printf("\n[4]. Consultar tarea por palabra clave");
        printf("\n[5]. Finalizar");
        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 0:
            agregarTareas(&listaTareasPendientes, &id);
            break;
        case 1:
            transferirNodosPorId(&listaTareasPendientes, &listaTareasRealizadas);
            break;
        case 2:
            printf("\nLista de pendientes:");
            mostrarLista(listaTareasPendientes);
            printf("\nLista de realizadas:");
            mostrarLista(listaTareasRealizadas);
            break;
        case 3:
            mostrarTareaID(listaTareasPendientes, listaTareasRealizadas);
            break;
        case 4:
            mostrarTareaPalabraClave(listaTareasPendientes, listaTareasRealizadas);
            break;
        default:
            break;
        }
    } while (opcion != 5);

   while(listaTareasPendientes != NULL)
   {
      free(listaTareasPendientes->T.descripcion);
      eliminarPrimerNodo(&listaTareasPendientes);
   }
   while(listaTareasRealizadas != NULL)
   {
      free(listaTareasRealizadas->T.descripcion);
      eliminarPrimerNodo(&listaTareasRealizadas);
   }
    return 0;

}

Nodo* crearListaVacia(){
    return NULL; 
}

Tarea cargarTarea(int id){
    Tarea nuevaT;
    char *buff = (char *)malloc(sizeof(char)*100); //RECORDAR LIBERAR
    nuevaT.TareaID = id;
    printf("\nIngrese la descripcion de la tarea: ");
    fflush(stdin);
    gets(buff);
    nuevaT.descripcion = (char *)malloc((strlen(buff)+1)*sizeof(char)); //RECORDAR LIBERAR
    strcpy(nuevaT.descripcion, buff);
    do {
        printf("\nIngrese la duracion de la tarea (entre 10 y 100): "); 
        scanf("%d",&nuevaT.Duracion); 
    } while (nuevaT.Duracion < 10 || nuevaT.Duracion > 100 );
    free(buff);
    return nuevaT;
}

void agregarTareas(Nodo** Lista, int *id){
    int decision;
    do
    {
        Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo)); //RECORDAR LIBERAR - > Se libera en la fn
        nuevo->siguiente = *Lista;
        *Lista = nuevo;
        nuevo->T = cargarTarea(*id);
        (*id)++;
        printf("\nDesea cargar otra tarea?");
        printf("\n[0]. No");
        printf("\n[1]. Si");
        printf("\nSeleccione una opcion: ");
        scanf("%d", &decision);
    } while (decision != 0);
}

void mostrarLista(Nodo* Lista){
    if (Lista == NULL)
    {
        printf("\nLa lista se encuentra vacia\n");
    }
    while (Lista != NULL)
    {
        printf("\n---TAREA---");
        printf("\nID: %d ", Lista->T.TareaID);
        printf("\nDescripcion: %s", Lista->T.descripcion);
        printf("\nDuracion de la tarea: %d\n", Lista->T.Duracion);
        Lista = Lista->siguiente;
    }

    
}

void transferirNodosPorId(Nodo **L1, Nodo **L2){
    int id, decision;
    do
    {
        printf("\nIngrese el id de la tarea que desea agregar a la lista de tareas realizadas: ");
        scanf("%d", &id);
        Nodo *actual = *L1; 
        Nodo *anterior = NULL;
        while (actual != NULL && actual ->T.TareaID != id) {
            anterior = actual;
            actual = actual->siguiente;
        }
        if(actual != NULL)
        {
            if (anterior != NULL)
            {
                anterior->siguiente = actual->siguiente;            
            } else
            {
                *L1 = actual->siguiente;
            }
            actual->siguiente = *L2;
            *L2 = actual;
        } else {
            printf("No se encontro una tarea con ese ID en la lista de tareas pendientes");
        }
        printf("\nDesea continuar transfiriendo tareas?");
        printf("\n[0]. No");
        printf("\n[1]. Si");
        printf("\nSeleccione una opcion: ");
        scanf("%d", &decision);
    } while (decision != 0);
    
}

void mostrarTareaID(Nodo* L1, Nodo* L2){
    int id;
    printf("\nIngrese el id de la tarea que desea buscar: ");
    scanf("%d", &id);
    while (L1 != NULL && L1->T.TareaID != id)
    {
        L1 = L1->siguiente;
    }
    if (L1 != NULL)
    {
        printf("\nLa tarea pertenece a la lista Pendientes");
        printf("\n---TAREA---");
        printf("\nID: %d ", L1->T.TareaID);
        printf("\nDescripcion: %s", L1->T.descripcion);
        printf("\nDuracion de la tarea: %d", L1->T.Duracion);
    } else
    {
        while (L2 != NULL && L2->T.TareaID != id)
        {
            L2 = L2->siguiente;
        }
        if (L2 != NULL)
        {
            printf("\nLa tarea pertenece a la lista Realizadas");
            printf("\n---TAREA---");
            printf("\nID: %d ", L2->T.TareaID);
            printf("\nDescripcion: %s", L2->T.descripcion);
            printf("\nDuracion de la tarea: %d", L2->T.Duracion);
        } else
        {
            printf("\nNo se encontro una tarea con ese ID en ninguna de las listas");
        }
    } 
}

void mostrarTareaPalabraClave(Nodo* L1, Nodo* L2){
    char *palabra;
    char *buff = (char *)malloc(sizeof(char)*100); //RECORDAR LIBERAR
    printf("\nIngrese la palabra clave a buscar: ");
    fflush(stdin);
    gets(buff);
    palabra = (char *)malloc((strlen(buff)+1)*sizeof(char)); //RECORDAR LIBERAR
    strcpy(palabra, buff);
    free(buff); //LIBERADO
    while (L1 != NULL && strstr(L1->T.descripcion, palabra) == NULL)
    {
        L1 = L1->siguiente;
    }
    if (L1 != NULL)
    {
        printf("\nLa tarea pertenece a la lista Pendientes");
        printf("\n---TAREA---");
        printf("\nID: %d ", L1->T.TareaID);
        printf("\nDescripcion: %s", L1->T.descripcion);
        printf("\nDuracion de la tarea: %d", L1->T.Duracion);
    } else
    {
        while (L2 != NULL && strstr(L2->T.descripcion, palabra) == NULL)
        {
            L2 = L2->siguiente;
        }
        if (L2 != NULL)
        {
            printf("\nLa tarea pertenece a la lista Realizadas");
            printf("\n---TAREA---");
            printf("\nID: %d ", L2->T.TareaID);
            printf("\nDescripcion: %s", L2->T.descripcion);
            printf("\nDuracion de la tarea: %d", L2->T.Duracion);
        } else
        {
            printf("\nNo se encontro una tarea con esa palabra en la descripcion de ninguna de las listas");
        }
    } 
    free(palabra); //LIBERADO
}

void eliminarPrimerNodo(Nodo **L){
    if (*L != NULL)
    {
        Nodo *aux = *L;
        *L = (*L)->siguiente;
        free(aux);
    }
}