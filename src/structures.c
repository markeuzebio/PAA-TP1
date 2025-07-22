#include <stdlib.h>

#include "../headers/structures.h"

Item *allocItems(int n)
{
    Item *item = (Item*) malloc(n * sizeof(Item));

    return item;
}

void freeItems(Item **pp_items)
{
    free(*pp_items);
    *pp_items = NULL;
}