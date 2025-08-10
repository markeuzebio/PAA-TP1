#include <stdio.h>
#include <stdlib.h>
#include "../headers/backtracking.h"

int *melhor_solucao = NULL;
int *solucao_atual = NULL;
int maior_lucro = 0;
// Retorna o maior entre dois inteiros
int maximo(int a, int b) {
    return (a > b) ? a : b;
}

// Função recursiva de backtracking
void mochila_backtracking(Item *itens, int indice_atual, int total_itens, int capacidade_mochila,
                          int lucro_atual, int peso_atual) {

    if (indice_atual == total_itens) {
        // Verifica se a solução atual é melhor do que a melhor encontrada até agora
        if (lucro_atual > maior_lucro) {
            maior_lucro = lucro_atual;
            for (int i = 0; i < total_itens; i++)
                melhor_solucao[i] = solucao_atual[i];
        }
        return;
    }

    // Tenta incluir o item atual, se não ultrapassar a capacidade
    if (peso_atual + itens[indice_atual].weigh <= capacidade_mochila) {
        solucao_atual[indice_atual] = 1;

        mochila_backtracking(itens, indice_atual + 1, total_itens, capacidade_mochila,
                             lucro_atual + itens[indice_atual].value,
                             peso_atual + itens[indice_atual].weigh);

        solucao_atual[indice_atual] = 0; // desfaz a inclusão para testar outros caminhos
    }

    // Tenta excluir o item atual
    mochila_backtracking(itens, indice_atual + 1, total_itens, capacidade_mochila,
                         lucro_atual, peso_atual);
}

// Exibe os resultados da melhor solução encontrada
void exibirResultadoBacktracking(Item *itens, int total_itens, int capacidade_mochila) {
    printf("Lucro máximo obtido: R$ %d\n", maior_lucro);
    printf("Itens selecionados:\n");

    int peso_total = 0;

    for (int i = 0; i < total_itens; i++) {
        if (melhor_solucao[i]) {
            printf("\t(Item %d: Valor = %d, Peso = %d)\n", i + 1, itens[i].value, itens[i].weigh);
            peso_total += itens[i].weigh;
        }
    }

    printf("Peso total na mochila: %d / %d\n", peso_total, capacidade_mochila);
}

// Função principal de interface para executar o backtracking
int executarBacktracking(Backpack *mochila) {
    int total_itens = mochila->items_amount;
    int capacidade_mochila = mochila->weigh;
    Item *itens = mochila->items;

    // Aloca vetores para armazenar as soluções
    melhor_solucao = (int*) calloc(total_itens, sizeof(int));
    solucao_atual = (int*) calloc(total_itens, sizeof(int));

    if (melhor_solucao == NULL || solucao_atual == NULL)
        return -1;

   maior_lucro = 0;

    #ifdef ENABLE_METRICS
        clock_t clock_begin;
        clock_t clock_end;
        double seconds;

        printf("----- REALIZANDO METRICAS DO PROGRAMA -----\n");
        printf("Inicializando a medicao de clocks de CPU utilizada...\n");

        clock_begin = clock();
    #endif

    mochila_backtracking(itens, 0, total_itens, capacidade_mochila, 0, 0);
    exibirResultadoBacktracking(itens, total_itens, capacidade_mochila);
    
    #ifdef ENABLE_METRICS
        clock_end = clock();

        seconds = ((double) (clock_end - clock_begin) / CLOCKS_PER_SEC);

        printf("QUANTIDADE DE TICKS DE CLOCKS GASTOS PELA CPU: %ld\n", clock_end - clock_begin);
        printf("QUANTIDADE DE SEGUNDOS GASTOS PELA CPU: %lfs\n", seconds);
        printf("-------------------------------------------\n\n");
    #endif

    free(melhor_solucao);
    free(solucao_atual);

    return 0;
}
