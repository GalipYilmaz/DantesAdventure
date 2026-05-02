#ifndef ROOM_H
#define ROOM_H

#include "Item.h"
#include "Entity.h"

typedef struct Room {
    const char* description;
    struct Room* up;
    struct Room* down;
    struct Room* left;
    struct Room* right;
    Item* items;
    struct Entities* entities;
} Room;

typedef struct Entities {
    Entity* entity;
    struct Entities* next;
} Entities;

Room* createRoom(const char* description);
void connectRooms(Room* room1, Room* room2, const char* direction);
void displayRoom(const Room* room);
void addItemToRoom(Room* room, Item* item);
void removeItemFromRoom(Room* room, const char* itemName);
void addEntityToRoom(Room* room, Entity* entity);
Entity* findEntityInRoom(Room* room, const char* entityName);

#endif // ROOM_H
