#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cidade.h"
#include "lista.h"
#include <limits.h>

#define INF INT_MAX

struct no_
{
    Distancia* dist;
    NO* proximo;
};

struct lista_
{
    NO* inicio;
    NO* fim;
    int tam;
};

LISTA* listaCriar(){
    LISTA* lista = malloc(sizeof(LISTA));
    if (lista!=NULL)
    {
        lista->fim = lista->inicio = NULL;
        lista->tam=0;
    }
    return lista;
}

NO* noCriar(Distancia* dist){
    NO* no = malloc(sizeof(NO));
    if (no!=NULL)
    {
        no->dist = dist;
        no->proximo = NULL;
    }
    return no;
}

bool listaInserir(LISTA* lista, Distancia* dist){
    if (!(listaCheia(lista)))
    {
        NO* no = noCriar(dist);
        if (listaVazia(lista))
        {
            lista->inicio = lista->fim = no;
        }
        else
        {
            lista->fim->proximo = no;
            lista->fim = no;
        }
        lista->tam++;
        return true;
    }
    return false;
}

int buscaDist(LISTA* lista, int a, int b){
    if (!(listaVazia(lista)))
    {
        NO* aux = lista->inicio;
        while (aux != NULL)
        {
            if ((aux->dist->cidadeA == a && aux->dist->cidadeB == b) ||
                (aux->dist->cidadeA == b && aux->dist->cidadeB == a))
            {
                return aux->dist->distancia;
            }
            aux = aux->proximo;
        }
    }
    return -1; // Indicar que não há caminho
}

void listaApagar(LISTA** lista){
    if (*lista!=NULL)
    {
        NO* aux;
        while ((*lista)->inicio!=NULL)
        {
            aux = (*lista)->inicio;
            (*lista)->inicio = (*lista)->inicio->proximo;
            free(aux);
        }
        free(*lista);
        *lista=NULL;
    }
}

bool listaCheia(LISTA* lista){
    if(lista!=NULL)
    {
        NO* teste = malloc(sizeof(NO));
        if (teste != NULL)
        {
            free(teste);
            return false;
        }
    }
    return true;
}

bool listaVazia(LISTA* lista){
    if (lista != NULL)
        return !(lista->tam);
    return true; 
}

void printLista(LISTA* lista){
    if (!listaVazia(lista))
    {
        NO* aux = lista->inicio;
        while (aux!=NULL)
        {
            printf("%d %d %d\n",aux->dist->cidadeA, aux->dist->cidadeB, aux->dist->distancia);
            aux = aux->proximo; 
        }
    }
}

