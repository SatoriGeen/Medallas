#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo
{
    char nombre[50];
    char pais[25];
    int puntaje;
    struct nodo *derecha;
    struct nodo *izquierda;
};

void insertar(struct nodo **raiz, char nombre [], char pais[], int puntaje)
{
    struct nodo *aInsertar = (struct nodo *)malloc(sizeof(struct nodo));
    int i;
    for(i = 0; nombre[i] != 0; i++)
        aInsertar->nombre [i] = nombre[i];
    aInsertar->nombre[i] = 0;
    for(i = 0; pais[i]; i++)
        aInsertar->pais [i] = pais [i];
    aInsertar->pais [i] = 0;
    aInsertar->puntaje = puntaje;
    aInsertar->derecha = NULL;
    aInsertar->izquierda = NULL;
    
    struct nodo *aux1, *aux2;
    aux1 = *raiz;
    if(aux1 == NULL)
        *raiz = aInsertar;
    else
    {
        while(aux1 != NULL)
        {
            aux2 = aux1;
            if(strcmp(nombre, aux1->nombre) > 0)
            {
                aux1 = aux1->derecha;
                if(aux1 == NULL)
                    aux2->derecha = aInsertar;
            }
            else
            {
                aux1 = aux1->izquierda;
                if(aux1 == NULL)
                    aux2->izquierda = aInsertar;
            }
        }
    }
}

struct nodo*buscarPorNombre(struct nodo *raiz, char nombre[])
{
    struct nodo *aux1, *aux2;
    aux1 = raiz;
    if(aux1 == NULL)
        return NULL;
    while(aux1 != NULL)
    {
        aux2 = aux1;
        if(strcmp(nombre, aux1->nombre) > 0)
        {
            aux1 = aux1->derecha;
            if(aux1 == NULL)
                return NULL;
        }
        else if(strcmp(nombre, aux1->nombre) < 0)
        {
            aux1 = aux1->izquierda;
            if(aux1 == NULL)
                return NULL;
        }
        else
            return aux1;
    }
}

int sumaPuntosPais(struct nodo *raiz, char pais[])
{
    int puntaje = 0;
    if(raiz != NULL)
    {
        if(strcmp(raiz->pais, pais) == 0)
            puntaje = raiz->puntaje;
        
        puntaje = puntaje + sumaPuntosPais(raiz->derecha, pais);
        puntaje = puntaje + sumaPuntosPais(raiz->izquierda, pais);
    }
    return puntaje; 
}

void inorden(struct nodo *raiz)
{
    if(raiz != NULL)
    {
        printf("Nombre: %s\t", raiz->nombre);
        printf("Pais: %s\t", raiz->pais);
        printf("Medalla: ");
        if(raiz->puntaje == 10)
            printf("Oro\n");
        else if(raiz->puntaje == 5)
            printf("Plata\n");
        else if(raiz->puntaje == 2)
            printf("Bronce\n");

        inorden(raiz->derecha);
        inorden(raiz->izquierda);
    }
}

int main()
{
    struct nodo *raizOro = NULL;
    struct nodo *raizPlata = NULL;
    struct nodo *raizBronce = NULL;

    FILE *miArchivo;
    miArchivo = fopen("datos de arbol.txt", "r");
    char nombre[50], pais[25];
    int puntaje;
    while(fscanf(miArchivo, "%s", nombre) != EOF)
    {
        fscanf(miArchivo, "%s", pais);
        fscanf(miArchivo, "%d", & puntaje);
        if(puntaje == 10)
            insertar(&raizOro, nombre, pais, puntaje);
        else if(puntaje == 5)
            insertar (&raizPlata, nombre, pais, puntaje);
        else if(puntaje == 2)
            insertar(&raizBronce, nombre,pais, puntaje);
    }

    printf("Buscar atleta y compatriotas\nNombre: ");
    scanf("%s", nombre);
    struct nodo *aux = buscarPorNombre(raizOro, nombre);
    if(aux == NULL)
        aux = buscarPorNombre(raizPlata, nombre);
    if(aux == NULL)
        aux = buscarPorNombre(raizBronce, nombre);

    if(aux == NULL)
        printf("No existe\n");
    else
    {
        if(aux->puntaje == 10)
            printf("Su medalla es de Oro");
        else if(aux->puntaje == 5)
            printf("Su medalla es de Plata");
        else if(aux->puntaje == 2)
            printf("Su medalla es de Bronce");
        printf("\nEl puntaje total del pais %s es de ", aux->pais);
        int puntaje = sumaPuntosPais(raizOro, aux->pais);
        puntaje = puntaje + sumaPuntosPais(raizPlata, aux->pais);
        puntaje = puntaje + sumaPuntosPais(raizBronce, aux->pais);
        printf("%d", puntaje);
    }
}
