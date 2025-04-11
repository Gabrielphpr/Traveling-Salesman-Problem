#ifndef LISTA_H
    #define LISTA_H
    #define inicial 0
    #define ERRO -32000

    #include "cidade.h"
    #include <stdbool.h>

    typedef struct no_ NO;
    typedef struct lista_ LISTA;

    LISTA* listaCriar();
    bool listaInserir(LISTA* lista, Distancia* dist);
    int buscaDist(LISTA* lista, int a, int b);
    void listaApagar(LISTA** lista);
    bool listaCheia(LISTA* lista);
    bool listaVazia(LISTA* lista);
    void printLista(LISTA* lista);
    
#endif