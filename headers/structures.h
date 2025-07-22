#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

typedef int WeighType;
typedef int ValueType;

typedef struct item {
    ValueType value;
    WeighType weigh;
} Item;

typedef struct backpack {
    WeighType weigh;
    Item *items;
    int items_amount;
} Backpack;

Item *allocItems(int n);
void freeItems(Item **pp_item);

#endif