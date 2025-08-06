#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../headers/dynamic.h"

// #define ENABLE_METRICS

typedef struct memo {
    int items_amount;
    int capacity;
    int **table;
} Memo;

static Memo m;

int **allocMemoTable(unsigned int capacity, unsigned int items_amount)
{
    m.table = (int**) malloc((items_amount + 1) * sizeof(int*));

    if(m.table == NULL)
        return NULL;

    for(unsigned int i = 0 ; i < items_amount + 1 ; i++)
    {
        m.table[i] = (int*) malloc((capacity + 1) * sizeof(int));

        if(m.table[i] == NULL)
            return NULL;
        else
            for(unsigned int j = 0 ; j <= capacity ; j++)
                m.table[i][j] = -1;
    }

    m.capacity = capacity;
    m.items_amount = items_amount;

    return m.table;
}

void freeMemoTable()
{
    for(unsigned int i = 0 ; i <= m.items_amount ; i++)
        free(m.table[i]);

    free(m.table);
}

int maxValue(int a, int b)
{
    return a > b ? a : b;
}

/*
    n: amount of items currently in snapsack
    m: capacity of snapsack
*/
int dynamic(Item *items, int amount_items, int capacity)
{
    int res1;
    int res2;

    if(amount_items == 0 || capacity == 0)
        return 0;

    res1 = res2 = 0;

    // If result has already been calculated, skip it
    if(m.table[amount_items][capacity] > -1)
        return m.table[amount_items][capacity];

    if(items[amount_items - 1].weigh > capacity)
        res2 = dynamic(items, amount_items - 1, capacity);
    else
    {
        res1 = dynamic(items, amount_items - 1, capacity - items[amount_items - 1].weigh) + items[amount_items - 1].value;
        res2 = dynamic(items, amount_items - 1, capacity);
    }

    m.table[amount_items][capacity] = maxValue(res1, res2);

    return m.table[amount_items][capacity];
}

void showProfitAndItems(Item *items, int profit)
{
    printf("Lucro: R$ %d\n", profit);
    printf("Itens colocados na mochila:\n");

    int i = m.items_amount;
    int j = m.capacity;

    while(i > 0 && j > 0)
    {
        if(m.table[i][j] != m.table[i - 1][j])
        {
            printf("\t(Item: %d, Valor: %d, Peso: %d)\n", i, items[i - 1].value, items[i - 1].weigh);
            j = j - items[i - 1].weigh;
        }

        i--;
    }
}

int dynamicApproch(Backpack *b)
{
    int profit;

    if(allocMemoTable(b->weigh, b->items_amount) == NULL)
        return -1;

    #ifdef ENABLE_METRICS
        clock_t clock_begin;
        clock_t clock_end;
        double seconds;

        printf("----- REALIZANDO METRICAS DO PROGRAMA -----\n");
        printf("Inicializando a medicao de clocks de CPU utilizada...\n");

        clock_begin = clock();
    #endif

    profit = dynamic(b->items, b->items_amount, b->weigh);

    #ifdef ENABLE_METRICS
        clock_end = clock();

        seconds = ((double) (clock_end - clock_begin) / CLOCKS_PER_SEC);

        printf("QUANTIDADE DE TICKS DE CLOCKS GASTOS PELA CPU: %ld\n", clock_end - clock_begin);
        printf("QUANTIDADE DE SEGUNDOS GASTOS PELA CPU: %lfs\n", seconds);
        printf("-------------------------------------------\n\n");

	showProfitAndItems(b->items, profit);
    #endif

    freeMemoTable();

    return 0;
}
