#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create a new player
Player* createPlayer() {
    Player* player = malloc(sizeof(Player));
    if (!player) return NULL;

    player->name = "Dante";
    player->health = 400;
    player->strength = 75;

    // Initialize inventory
    player->inventory = malloc(sizeof(Inventory));  // Allocate memory for inventory
    if (!player->inventory) {
        free(player);
        return NULL;
    }
    player->inventory->items = NULL;
    player->inventory->inventorySize = 4;
    player->inventory->currentSize = 0;


    pickupItem(player,"Basic Sword");
    pickupItem(player, "Basic Helmet");
    pickupItem(player, "Basic Breastplate");

    player->currentRoom = NULL;

    return player;
}

// Destroy a player and free memory
void destroyPlayer(Player* player) {
    if (!player) return;

    // Free inventory items first
    Item* currentItem = player->inventory->items;
    while (currentItem) {
        Item* next = currentItem->item;
        destroyItem(currentItem);
        currentItem = next;
    }

    free(player->inventory);
    free(player);
}

// Display player stats
void displayPlayerStats(const Player* player) {
    if (!player) return;
    printf("\n");
    printf("Player Name: %s\n", player->name);
    printf("Health: %d\n", player->health);
    printf("Strength: %d\n", player->strength);
    printf("Inventory Size: %d\n",player->inventory->inventorySize);
    printf("\n");
}

// Display player inventory
void displayInventory(const Player* player) {
    printf("\n");
    if (!player || !player->inventory) return;

    Item* currentItem = player->inventory->items;
    int index = 1;


    while (currentItem != NULL) {
        printf("%d: %s\n", index, currentItem->name);
        currentItem = currentItem->item;
        index++;
    }
    printf("\n");
}

// Move player to another room
void move(Player* player, Room* currentRoom, const char* direction) {
    if (!player || !currentRoom || !direction) return;

    Room* nextRoom = NULL;

    if (strcmp(direction, "up") == 0) {
        nextRoom = currentRoom->up;
    } else if (strcmp(direction, "down") == 0) {
        nextRoom = currentRoom->down;
    } else if (strcmp(direction, "left") == 0) {
        nextRoom = currentRoom->left;
    } else if (strcmp(direction, "right") == 0) {
        nextRoom = currentRoom->right;
    }

    if (nextRoom) {
        printf("\n%s moves to the %s.\n", player->name, direction);
        player->currentRoom = nextRoom;
        displayRoom(nextRoom);
        printf("\n");
    } else {
        printf("\nThere is no room in that direction.\n");
    }
}

// Attack a creature
void attack(Player* player, Entity* creature) {
    if (!player || !creature) {
        printf("Invalid player or creature.\n");
        return;
    }
    printf("\n");
    printf("%s attacks %s!\n", player->name, creature->name);
    entityTakeDamage(creature, player->strength);
    entityTakeDamage((Entity*)player, creature->strength);

    if (creature->health > 0) {
        printf("\n");
        printf("%s has %d HP remaining.\n", creature->name, creature->health);
        printf("%s has %d HP remaining.\n", player->name, player->health);
        printf("\n");
    }
}

// Pick up an item and add it to the inventory
void pickupItem(Player* player, const char* itemName) {
    if (!player || !player->inventory) {
        printf("Inventory not initialized.\n");
        printf("\n");
        return;
    }

    if (player->inventory->currentSize >= player->inventory->inventorySize) {
        printf("\nInventory is full.\n");
        return;
    }


    if (isItemInInventory(player->inventory, itemName)) {
        printf("\nItem '%s' already exists in your inventory.\n", itemName);
        return;
    }


    Item* newItem = createItem(itemName);
    if (!newItem) {
        printf("\nFailed to create item.\n");
        return;
    }


    newItem->item = player->inventory->items;
    player->inventory->items = newItem;
    player->inventory->currentSize++;

    applyItemEffect(player,newItem,1);
}



// Drop an item from the inventory
void dropItem(Player* player, const char* itemName) {
    if (!player || !player->inventory || !player->inventory->items) {
        printf("\nNo items in the inventory.\n");
        return;
    }

    Item* current = player->inventory->items;


    if (strcmp(current->name, itemName) == 0) {
        player->inventory->items = current->item;
        applyItemEffect(player, current, -1);
        destroyItem(current);
        player->inventory->currentSize--;
        printf("Dropped item: %s\n\n", itemName);
        return;
    }


    while (current->item) {
        if (strcmp(current->item->name, itemName) == 0) {
            Item* temp = current->item;
            current->item = temp->item;
            applyItemEffect(player, temp, -1);
            destroyItem(temp);
            player->inventory->currentSize--;
            printf("\nDropped item: %s\n", itemName);
            return;
        }
        current = current->item;
    }

    printf("\nItem '%s' not found in inventory.\n", itemName);
}

void applyItemEffect(Player* player, Item* item, int multiplier) {
    if (!player || !item) return;

    if (strcmp(item->name, "Sword of Kings") == 0) {
        player->strength += 50 * multiplier;
        printf("\nYour strength %s by 50.\n", (multiplier > 0) ? "increased" : "decreased");
    } else if (strcmp(item->name, "The Warlord's Helmet") == 0) {
        player->health += 50 * multiplier;
        printf("\nYour health %s by 50.\n", (multiplier > 0) ? "increased" : "decreased");
    } else if (strcmp(item->name, "The Warlord's Breastplate") == 0) {
        player->health += 150 * multiplier;
        printf("\nYour health %s by 150.\n", (multiplier > 0) ? "increased" : "decreased");
    } else if (strcmp(item->name, "Dead Man's Bag") == 0) {
        player->inventory->inventorySize += 4 * multiplier;
        printf("\nYour inventory capacity %s by 4.\n", (multiplier > 0) ? "increased" : "decreased");
    } else if (strcmp(item->name, "The Heart of the Mountain") == 0) {
        player->strength += 100 * multiplier;
        printf("\nYour strength %s by 100.\n", (multiplier > 0) ? "increased" : "decreased");
    } else if (strcmp(item->name, "Healing Potion I") == 0 ||
               strcmp(item->name, "Healing Potion II") == 0 ||
               strcmp(item->name, "Healing Potion III") == 0 ||
               strcmp(item->name, "Healing Potion IV") == 0) {

        if (multiplier > 0) {
            printf("\nYour health increased by 100 points!\n");
            player->health += 100;
        }
               }
}


// Look around in the room
void look(Room* room) {
    if (!room) {
        printf("Invalid room.\n");
        return;
    }
    printf("\n");
    displayRoom(room);
    printf("\n");
}


int isItemInInventory(const Inventory* inventory, const char* itemName) {
    Item* currentItem = inventory->items;

    while (currentItem != NULL) {
        if (strcmp(currentItem->name, itemName) == 0) {
            return 1;
        }
        currentItem = currentItem->item;
    }
    return 0;
}
