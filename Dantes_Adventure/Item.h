#ifndef ITEM_H
#define ITEM_H

typedef struct Item {
    char* name;
    struct Item* item;
} Item;

Item* createItem(const char* name);
void destroyItem(Item* item);
void displayItems(const Item* items);


#endif //ITEM_H
