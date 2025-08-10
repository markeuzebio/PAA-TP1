#ifndef MOCHILABRANCH_H
#define MOCHILABRANCH_H

#include "../headers/structures.h"
#include <stdbool.h>

#define MAX_QUEUE_SIZE 10000

typedef struct Node{
    int level;
    WeighType weight;
    ValueType profit;
    float bound;
    bool *selected_items;

}Node;


typedef struct priority_queue {
    Node **nodes;
    int size;
} PriorityQueue;

int branchAndBoundApproach(Backpack*);

#endif