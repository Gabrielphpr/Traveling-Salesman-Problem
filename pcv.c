// pcv.c
#include "pcv.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define INF INT_MAX
#define MIN(a,b) (((a)<(b))?(a):(b))

void permutacao(int* caminho, int cidade_inicial, int l, int r, int* menor_distancia,
               LISTA* distancias, int n, int* melhor_trajeto)
{
    if (l == r)
    {
        // Calcular a distância total para esta permutação
        int total_distance = 0;

        // Distância da cidade inicial para a primeira cidade no trajeto
        int dist = buscaDist(distancias, cidade_inicial, caminho[0]);
        if (dist == -1)
        {
            // Rota inválida
            return;
        }
        total_distance += dist;

        // Distâncias entre as cidades no trajeto
        for (int i = 0; i < n - 1; i++)
        {
            dist = buscaDist(distancias, caminho[i], caminho[i + 1]);
            if (dist == -1)
            {
                // Rota inválida
                return;
            }
            total_distance += dist;
        }

        // Distância da última cidade de volta para a cidade inicial
        dist = buscaDist(distancias, caminho[n - 1], cidade_inicial);
        if (dist == -1)
        {
            // Rota inválida
            return;
        }
        total_distance += dist;

        // Mensagem de depuração
       // printf("Permutação atual: %d ", cidade_inicial + 1); // Converte para 1-based
        /*for (int i = 0; i < n; i++)
        {
            printf("%d ", caminho[i] + 1); // Converte para 1-based
        }
        printf("%d\n", cidade_inicial + 1); // Retorna à cidade inicial*/

        //printf("Distância total atual: %d\n", total_distance);

        // Verificar se encontramos um caminho menor
        if (total_distance < *menor_distancia)
        {
            *menor_distancia = total_distance;

            // Preenche o melhor trajeto sem a cidade inicial
            for (int i = 0; i < n; i++)
            {
                melhor_trajeto[i] = caminho[i];
            }
            // A cidade inicial será adicionada na impressão
        }
    }
    else
    {
        for (int i = l; i <= r; i++)
        {
            // Trocar os elementos do caminho
            int temp = caminho[l]; //4
            caminho[l] = caminho[i]; //5
            caminho[i] = temp; //4

            // Recursivamente gerar permutações
            permutacao(caminho, cidade_inicial, l + 1, r, menor_distancia, distancias, n, melhor_trajeto);

            // Desfazer a troca de elementos
            temp = caminho[l];
            caminho[l] = caminho[i];
            caminho[i] =temp;
        }
    }
}

int heldKarp(LISTA *distancias, int num_cidades, int cidade_inicial)
{
    int n = num_cidades;
    int total_masks = 1 << n;

    // Alocação dinâmica da tabela dp
    int **dp = malloc(total_masks * sizeof(int *));
    if (!dp)
    {
        printf("Erro de alocação de memória para dp\n");
        return -1;
    }
    for (int i = 0; i < total_masks; i++)
    {
        dp[i] = malloc(n * sizeof(int));
        if (!dp[i])
        {
            printf("Erro de alocação de memória para dp[%d]\n", i);
            // Libera a memória já alocada
            for (int j = 0; j < i; j++)
            {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
        for (int j = 0; j < n; j++)
        {
            dp[i][j] = INF;
        }
    }

    // Definir a condição inicial: apenas a cidade inicial foi visitada
    dp[1 << cidade_inicial][cidade_inicial] = 0;

    // Preencher a tabela de memorização
    for (int mascara = 0; mascara < (1 << n); mascara++)
    {
        for (int u = 0; u < n; u++)
        {
            // Se a cidade 'u' está no subconjunto indicado por 'mascara'
            if (mascara & (1 << u))
            {
                // Itera sobre todas as cidades 'v' que não estão no subconjunto
                for (int v = 0; v < n; v++)
                {
                    if (!(mascara & (1 << v)))
                    {
                        int nova_mascara = mascara | (1 << v);
                        int dist = buscaDist(distancias, u, v); // 0-based
                        if (dist != -1 && dp[mascara][u] != INF)
                        {
                            int new_dist = dp[mascara][u] + dist;
                            if (new_dist < dp[nova_mascara][v])
                            {
                                dp[nova_mascara][v] = new_dist;
                            }
                        }
                    }
                }
            }
        }
    }

    // Encontrar a menor distância que visita todas as cidades e retorna à cidade inicial
    int menor_distancia = INF;
    int all_visited = (1 << n) - 1;
    for (int u = 0; u < n; u++)
    {
        if (u == cidade_inicial)
            continue;                                        // Não considerar a cidade inicial aqui
        int dist = buscaDist(distancias, u, cidade_inicial); // 0-based
        if (dist != -1 && dp[all_visited][u] != INF)
        {
            int total = dp[all_visited][u] + dist;
            if (total < menor_distancia)
            {
                menor_distancia = total;
            }
        }
    }

    // Libera a memória alocada para dp
    for (int i = 0; i < total_masks; i++)
    {
        free(dp[i]);
    }
    free(dp);

    // Retorna a menor distância encontrada ou -1 se não houver trajeto válido
    return (menor_distancia == INF) ? -1 : menor_distancia;
}