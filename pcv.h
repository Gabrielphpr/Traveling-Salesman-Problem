// pcv.h
#ifndef PCV_H
#define PCV_H

#include "cidade.h"
#include "lista.h"

// Função para gerar todas as permutações e calcular o menor trajeto
void permutacao(int *caminho, int cidade_inicial, int l, int r, int *menor_distancia,
                LISTA *distancias, int n, int *melhor_trajeto);
int heldKarp(LISTA* distancias, int num_cidades, int cidade_inicial);
#endif // PCV_H
