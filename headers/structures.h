#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

typedef unsigned int WeighType;

typedef struct item {
    double value;
    WeighType weigh;
} Item;

typedef struct backpack {
    WeighType weigh;
    Item *items;
    unsigned int items_amount;
} Backpack;

Item *allocItems(unsigned int n);
void freeItems(Item **pp_item);

#endif