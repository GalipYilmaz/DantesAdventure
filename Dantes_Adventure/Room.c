#include "Room.h"
#include "Entity.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Item.h"

// Create a new room
Room* createRoom(const char* description) {
    Room* newRoom = malloc(sizeof(Room));
    if (!newRoom) return NULL;

    newRoom->description = strdup(description);
    newRoom->up = NULL;
    newRoom->down = NULL;
    newRoom->left = NULL;
    newRoom->right = NULL;
    newRoom->items = NULL;
    newRoom->entities = NULL;
    return newRoom;
}

// Connect two rooms
void connectRooms(Room* room1, Room* room2, const char* direction) {
    if (!room1 || !room2 || !direction) return;

    if (strcmp(direction, "up") == 0) {
        room1->up = room2;
        room2->down = room1;
    } else if (strcmp(direction, "down") == 0) {
        room1->down = room2;
        room2->up = room1;
    } else if (strcmp(direction, "left") == 0) {
        room1->left = room2;
        room2->right = room1;
    } else if (strcmp(direction, "right") == 0) {
        room1->right = room2;
        room2->left = room1;
    }
}

// Display details of a room
void displayRoom(const Room* room) {
    if (!room) return;

    printf("%s\n", room->description);
    printf("\n");

    if (room->entities) {
        printf("Entities in the room:\n");
        Entities* current = room->entities;
        while (current) {
            printf("- %s (HP: %d, Damage: %d)\n", current->entity->name, current->entity->health, current->entity->strength);
            current = current->next;
        }
    }

    if (room->items) {
        printf("\n");
        printf("Items in the room:\n");
        displayItems(room->items);
        printf("\n");
    }

    if (room->up) printf("There is a room above.\n");
    if (room->down) printf("There is a room below.\n");
    if (room->left) printf("There is a room to the left.\n");
    if (room->right) printf("There is a room to the right.\n");

}

// Add an item to a room
void addItemToRoom(Room* room, Item* item) {
    if (!room || !item) return;

    item->item = room->items;
    room->items = item;
}

// Remove an item from a room
void removeItemFromRoom(Room* room, const char* itemName) {
    if (room == NULL || room->items == NULL) {
        printf("No items in this room.\n");
        return;
    }

    Item* currentItem = room->items;
    Item* previousItem = NULL;


    if (strcmp(currentItem->name, itemName) == 0) {
        room->items = currentItem->item;
        destroyItem(currentItem);
        printf("Removed item from the  room: %s\n\n", itemName);
        return;
    }

    // Listedeki diğer öğeleri kontrol et
    while (currentItem != NULL) {
        if (strcmp(currentItem->name, itemName) == 0) {
            previousItem->item = currentItem->item;
            destroyItem(currentItem);
            printf("Removed item from the room: %s\n", itemName);
            return;
        }
        previousItem = currentItem;
        currentItem = currentItem->item;
    }


    printf("Item '%s' not found in this room.\n", itemName);

}

// Add an entity to a room
void addEntityToRoom(Room* room, Entity* entity) {
    if (!room || !entity) return;

    Entities* newNode = malloc(sizeof(Entities));
    if (!newNode) {
        printf("Memory allocation failed for EntityNode.\n");
        return;
    }

    newNode->entity = entity;
    newNode->next = room->entities;
    room->entities = newNode;
}


// Find an entity in the room by name
Entity* findEntityInRoom(Room* room, const char* entityName) {
    if (!room || !entityName) return NULL;

    Entities* current = room->entities;
    while (current) {
        if (strcmp(current->entity->name, entityName) == 0) {
            return current->entity;
        }
        current = current->next;
    }
    return NULL;
}
