// main.c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "cidade.h"
#include "lista.h"
#include "pcv.h"


#define INF INT_MAX

int main(int argc, char *argv[]) {
    // Verifica se o nome do arquivo foi passado
    if (argc < 2) {
        printf("Uso: %s <arquivo_de_entrada>\n", argv[0]);
        return 1;
    }

    // Abre o arquivo de entrada
    FILE* p = fopen(argv[1], "r");
    if (p == NULL) {
        printf("Erro ao abrir o arquivo %s\n", argv[1]);
        return 1;
    }

    // Leitura dos dados iniciais
    int num_cidades;
    fscanf(p, "%d", &num_cidades);

    int cidade_inicial;
    fscanf(p, "%d", &cidade_inicial);
    cidade_inicial -= 1; // Convertendo para 0-based

    int num_estradas;
    fscanf(p, "%d", &num_estradas);

    // Inicializa a lista de distâncias
    LISTA* distancias = listaCriar();
    if (distancias == NULL) {
        printf("Erro ao criar a lista de distâncias\n");
        fclose(p);
        return 1;
    }

    // Leitura das estradas e inserção na lista de distâncias
    for (int i = 0; i < num_estradas; i++) {
        int a, b, d;
        fscanf(p, "%d %d %d", &a, &b, &d);

        Distancia* dist = malloc(sizeof(Distancia));
        if (dist == NULL) {
            printf("Erro de alocação de memória\n");
            fclose(p);
            listaApagar(&distancias);
            return 1;
        }
        dist->cidadeA = a - 1; // Convertendo para 0-based
        dist->cidadeB = b - 1; // Convertendo para 0-based
        dist->distancia = d;

        // Insere a distância na lista
        if (!listaInserir(distancias, dist)) {
            printf("Falha ao inserir na lista\n");
            free(dist);
            fclose(p);
            listaApagar(&distancias);
            return 1;
        }
    }

    fclose(p);  // Fecha o arquivo após a leitura

    // ** Abordagem de Força Bruta **
    // Inicializa o caminho com as cidades (exceto a inicial)
    int n = num_cidades - 1;
    int* caminho = malloc(n * sizeof(int));
    if (caminho == NULL) {
        printf("Erro de alocação de memória para caminho\n");
        listaApagar(&distancias);
        return 1;
    }

    // Preenche o caminho com as cidades diferentes da inicial
    int index = 0;
    for (int i = 0; i < num_cidades; i++) {  // Agora de 0 a num_cidades -1
        if (i != cidade_inicial) {
            caminho[index++] = i;
        }
    }

    // Inicializa as variáveis para armazenar a menor distância e o melhor trajeto
    int menor_distancia = INF;
    int* melhor_trajeto = malloc(n * sizeof(int));  // Inclui apenas as cidades visitadas
    if (melhor_trajeto == NULL) {
        printf("Erro de alocação de memória para melhor_trajeto\n");
        free(caminho);
        listaApagar(&distancias);
        return 1;
    }

    // Medindo o tempo de execução da Força Bruta
    clock_t inicio = clock();  // Marca o início

    // Chama a função de permutação (força bruta)
    permutacao(caminho, cidade_inicial, 0, n - 1, &menor_distancia, distancias, n, melhor_trajeto);

    clock_t fim = clock();  // Marca o fim
    double tempoForcaBruta = (double)(fim - inicio) / CLOCKS_PER_SEC;


    // Imprime o resultado da força bruta
    if (menor_distancia != INF) {
        printf("Solução Força Bruta:\n");
        printf("Menor trajeto: %d\n", menor_distancia);
        printf("Caminho: %d ", cidade_inicial + 1);  // Inicia o caminho com a cidade inicial (1-based)
        for (int i = 0; i < n; i++) {
            printf("%d ", melhor_trajeto[i] + 1); // Converte para 1-based
        }
        printf("%d\n", cidade_inicial + 1);  // Retorna à cidade inicial no final do caminho
         printf("Tempo de execução Força Bruta: %.6f segundos\n", tempoForcaBruta);
    }
    else {
        printf("Nenhum trajeto válido encontrado.\n");
    }

    // ** Abordagem de Programação Dinâmica (Held-Karp) **
    // Medindo o tempo de execução da Programação Dinâmica
    inicio = clock();  // Marca o início
    int menor_distancia_dp = heldKarp(distancias, num_cidades, cidade_inicial);

    fim = clock();  // Marca o fim
    double tempoDinamica = (double)(fim - inicio) / CLOCKS_PER_SEC;
    

    // Imprime o resultado da programação dinâmica
    printf("\nSolução Programação Dinâmica (Held-Karp):\n");
    if (menor_distancia_dp != -1) {  // heldKarp retorna -1 se não houver trajeto válido
        printf("Menor trajeto: %d\n", menor_distancia_dp);
        printf("Caminho: %d ", cidade_inicial + 1);  // Inicia o caminho com a cidade inicial (1-based)
        for (int i = 0; i < n; i++) {
            printf("%d ", melhor_trajeto[i] + 1); // Converte para 1-based
        }
        printf("%d\n", cidade_inicial + 1);  // Retorna à cidade inicial no final do caminho
        printf("Tempo de execução Programação Dinâmica: %.6f segundos\n", tempoDinamica);
    
    } else {
        printf("Nenhum trajeto válido encontrado.\n");
    }

    // Libera a memória alocada
    free(caminho);
    free(melhor_trajeto);
    listaApagar(&distancias);

    return 0;
}
