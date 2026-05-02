#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"

typedef struct Inventory {
    Item* items;
    int inventorySize;
    int currentSize;
} Inventory;

#endif //INVENTORY_H
