#ifndef PLAYER_H
#define PLAYER_H

#include "Inventory.h"
#include "Room.h"

typedef struct Player {
    char* name;
    int health;
    int strength;
    Inventory* inventory;
    Room* currentRoom;
} Player;

Player* createPlayer();
void destroyPlayer(Player* player);
void move(Player* player, Room* currentRoom, const char* direction) ;
void attack(Player* player, Entity* target);
void pickupItem(Player* player, const char* itemName);
void dropItem(Player* player, const char* itemName);
void applyItemEffect(Player* player, Item* item, int multiplier);
int isItemInInventory(const Inventory* inventory, const char* itemName);
void displayPlayerStats(const Player* player);
void displayInventory(const Player* player);
void look(Room* room);

#endif