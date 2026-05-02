#include "Item.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Creat Item
Item* createItem(const char* name) {
    Item* newItem = (Item*)malloc(sizeof(Item));
    if (newItem == NULL) {
        return NULL;
    }


    newItem->name = strdup(name);
    if (newItem->name == NULL) {
        free(newItem);
        return NULL;
    }

    return newItem;
}

// Destroy the item, free the allocated memory
void destroyItem(Item* item) {
    if (item == NULL) return;

    if (item->name != NULL) {
        free(item->name);
    }

    free(item);
}


void displayItems(const Item* items) {
    const Item* current = items;
    while (current) {
        printf("- %s\n", current->name);
        current = current->item;
    }
}