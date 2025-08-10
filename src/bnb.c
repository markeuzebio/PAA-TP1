#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../headers/bnb.h"


int compareNodes(const void *a, const void *b) {
    Node *n1 = *(Node**)a;
    Node *n2 = *(Node**)b;
    return (n2->bound > n1->bound) - (n2->bound < n1->bound);
}

PriorityQueue *createPriorityQueue() {
    PriorityQueue *pq = malloc(sizeof(PriorityQueue));
    pq->nodes = malloc(sizeof(Node*) * MAX_QUEUE_SIZE);
    pq->size = 0;
    return pq;
}

void enqueue(PriorityQueue *pq, Node *node) {
    if (pq->size >= MAX_QUEUE_SIZE) return;
    pq->nodes[pq->size++] = node;
    qsort(pq->nodes, pq->size, sizeof(Node*), compareNodes);
}

Node* dequeue(PriorityQueue *pq) {
    if (pq->size == 0) return NULL;
    return pq->nodes[--pq->size];
}

bool isEmpty(PriorityQueue *pq) {
    return pq->size == 0;
}

void freeQueue(PriorityQueue *pq) {
    for (int i = 0; i < pq->size; i++) {
        free(pq->nodes[i]->selected_items);
        free(pq->nodes[i]);
    }
    free(pq->nodes);
    free(pq);
}

Node *createNode(int level, WeighType weight, ValueType profit, int items_amount) {
    Node *node = malloc(sizeof(Node));
    node->level = level;
    node->weight = weight;
    node->profit = profit;
    node->bound = 0.0f;
    node->selected_items = calloc(items_amount, sizeof(bool));
    return node;
}

Node *copyNode(Node *src, int items_amount) {
    Node *copy = createNode(src->level, src->weight, src->profit, items_amount);
    memcpy(copy->selected_items, src->selected_items, items_amount * sizeof(bool));
    return copy;
}


float calculateBound(Node *node, Backpack *b ){
    if(node->weight >= b->weigh){
        return 0;
    }

    WeighType totalWeight = node->weight;
    ValueType totalValue = node->profit;
    int i = node->level + 1;
    
    while(i < b->items_amount && totalWeight + b->items[i].weigh <= b->weigh){
        totalValue += b->items[i].value;
        totalWeight += b->items[i].weigh;
        i++;
    }

    if(i < b->items_amount){
        float ratio = (float)b->items[i].value/b->items[i].weigh;
        totalValue += (b->weigh - totalWeight) * ratio;
    }

    return totalValue;
}



int branchAndBoundApproach(Backpack *b) {
    int best_profit = 0;
    bool *best_items = calloc(b->items_amount, sizeof(bool));

    #ifdef ENABLE_METRICS
        clock_t clock_begin = clock();
    #endif

    Node *root = createNode(-1, 0, 0, b->items_amount);
    root->bound = calculateBound(root, b);

    PriorityQueue *pq = createPriorityQueue();
    enqueue(pq, root);

    while (!isEmpty(pq)) {
        Node *u = dequeue(pq);

        if (u->bound <= best_profit) {
            free(u->selected_items);
            free(u);
            continue;
        }

        int level = u->level + 1;
        if (level >= b->items_amount) {
            free(u->selected_items);
            free(u);
            continue;
        }

        Item current = b->items[level];

        // Incluir o item atual
        Node *incl = copyNode(u, b->items_amount);
        incl->level = level;
        incl->weight += current.weigh;
        incl->profit += current.value;
        incl->selected_items[level] = true;

        if (incl->weight <= b->weigh && incl->profit > best_profit) {
            best_profit = incl->profit;
            memcpy(best_items, incl->selected_items, b->items_amount * sizeof(bool));
        }

        incl->bound = calculateBound(incl, b);
        if (incl->bound > best_profit) {
            enqueue(pq, incl);
        } else {
            free(incl->selected_items);
            free(incl);
        }

        // Não incluir o item atual
        Node *excl = copyNode(u, b->items_amount);
        excl->level = level;
        excl->bound = calculateBound(excl, b);
        if (excl->bound > best_profit) {
            enqueue(pq, excl);
        } else {
            free(excl->selected_items);
            free(excl);
        }

        free(u->selected_items);
        free(u);
    }

    #ifdef ENABLE_METRICS
        clock_t clock_end = clock();
        double seconds = ((double)(clock_end - clock_begin) / CLOCKS_PER_SEC);

        printf("----- REALIZANDO METRICAS DO PROGRAMA -----\n");
        printf("QUANTIDADE DE TICKS DE CLOCKS GASTOS PELA CPU: %ld\n", clock_end - clock_begin);
        printf("QUANTIDADE DE SEGUNDOS GASTOS PELA CPU: %lfs\n", seconds);
        printf("-------------------------------------------\n\n");
    #endif

    // Exibir resultado
    printf("Lucro máximo: R$ %d\n", best_profit);
    printf("Itens colocados na mochila:\n");
    for (int i = 0; i < b->items_amount; i++) {
        if (best_items[i]) {
            printf("\t(Item: %d, Valor: %d, Peso: %d)\n", i+1, b->items[i].value, b->items[i].weigh);
        }
    }

    free(best_items);
    freeQueue(pq);

    return 0;
}
