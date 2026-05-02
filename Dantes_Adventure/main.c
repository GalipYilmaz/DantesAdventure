#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Entity.h"
#include "Player.h"
#include "Item.h"
#include "Room.h"


void gameScenario(Player* player) {
    Room* roomA = createRoom("Deserted Square");
    addItemToRoom(roomA, createItem("Dead Man's Bag"));
    addEntityToRoom(roomA, createPresetEntity(ORC));
    addEntityToRoom(roomA, createPresetEntity(SPIDER));

    Room* roomB = createRoom("Orc Outpost");
    addEntityToRoom(roomB, createPresetEntity(ORC));
    addEntityToRoom(roomB, createPresetEntity(UNDEAD));


    Room* roomC = createRoom("Cellar of Kings");
    addItemToRoom(roomC, createItem("Sword of Kings"));
    addEntityToRoom(roomC, createPresetEntity(SPIDER));
    addEntityToRoom(roomC, createPresetEntity(UNDEAD));

    Room* roomD = createRoom("Mystic Archives");
    addItemToRoom(roomD, createItem("Healing Potion I"));
    addEntityToRoom(roomD, createPresetEntity(ORC));
    addEntityToRoom(roomD, createPresetEntity(GOLEM));

    Room* roomE = createRoom("The Stone Sanctum");
    addEntityToRoom(roomE, createPresetEntity(GOLEM));
    addEntityToRoom(roomE, createPresetEntity(SPIDER));

    Room* roomF = createRoom("Eldritch Chamber");
    addItemToRoom(roomF, createItem("Healing Potion II"));
    addEntityToRoom(roomF, createPresetEntity(GOLEM));

    Room* roomG = createRoom("Luminous Sanctuary");
    addItemToRoom(roomG, createItem("The Heart of the Mountain"));
    addEntityToRoom(roomG, createPresetEntity(SPIDER));
    addEntityToRoom(roomG, createPresetEntity(ORC));

    Room* roomH = createRoom("Warlord's Helm Chamber");
    addItemToRoom(roomH, createItem("The Warlord's Helmet"));
    addEntityToRoom(roomH, createPresetEntity(UNDEAD));
    addEntityToRoom(roomH, createPresetEntity(SPIDER));

    Room* roomK = createRoom("Whispering Catacombs");
    addItemToRoom(roomK, createItem("Healing Potion III"));
    addEntityToRoom(roomK, createPresetEntity(UNDEAD));


    Room* roomL = createRoom("Shadowy Alcove");
    addEntityToRoom(roomL, createPresetEntity(UNDEAD));
    addEntityToRoom(roomL, createPresetEntity(SPIDER));

    Room* roomM = createRoom("The Warlord's Breastplate Chamber");
    addItemToRoom(roomM, createItem("The Warlord's Breastplate"));
    addEntityToRoom(roomM, createPresetEntity(UNDEAD));
    addEntityToRoom(roomM, createPresetEntity(ORC));


    Room* roomN = createRoom("Throne Room of The Necromancer");
    addItemToRoom(roomN, createItem("Healing Potion IV"));
    addEntityToRoom(roomN, createPresetEntity(NECROMANCER));

    connectRooms(roomA,roomB,"up");
    connectRooms(roomB,roomC,"left");
    connectRooms(roomC,roomD,"left");
    connectRooms(roomC,roomF,"up");
    connectRooms(roomD,roomE,"up");
    connectRooms(roomD,roomG,"left");
    connectRooms(roomE,roomF,"right");
    connectRooms(roomB,roomH,"right");
    connectRooms(roomH,roomK,"up");
    connectRooms(roomK,roomL,"right");
    connectRooms(roomL,roomM,"right");
    connectRooms(roomM,roomN,"up");

    player->currentRoom = roomA;
}
void displayIntro() {
    printf("*****************THE INTRO STORY*****************\n\n");
    FILE* file = fopen("Intro.txt", "r");
    if (file == NULL) {
        printf("Failed to open Intro.txt\n");
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
}
void displayMap() {
    printf("*****************THE MOUNTAIN MAP*****************\n");
    FILE* file = fopen("Map.txt", "r");
    if (file == NULL) {
        printf("Failed to open Map.txt\n");
        return;
    }
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
    printf("\n");
}
void displayRoomDescriptions() {
    printf("*****************ROOM DESCRIPTIONS*****************\n\n");
    FILE* file = fopen("RoomDescriptions.txt", "r");
    if (file == NULL) {
        printf("Failed to open Map.txt\n");
        return;
    }
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
    printf("\n");
}

void endGameWithWin() {
    printf("Congratulations! You killed the necromancer and won the game. You avenged your family.\n");
    printf("Press any key and enter to exit...");
    getchar();
    if (getchar()) {
        exit(0);
    }
}



int main(void) {
    printf("The game is started.\n");
    displayIntro();
    Player* player = createPlayer();

    gameScenario(player);

    char command[256];
    while (1) {

        printf("Enter command (move, look, attack, pickup, drop, inventory, player stats, map,room info ,exit): ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0) {
            break;
        }

        if (strncmp(command, "move ", 5) == 0) {
            move(player,player->currentRoom,command + 5);
        }
        else if (strncmp(command, "look", 5) == 0) {
            look(player->currentRoom);
        }
        else if (strncmp(command, "attack ", 7) == 0) {
            Entity* target = findEntityInRoom(player->currentRoom, command + 7);
            if (target) {
                attack(player, target);
                if (player->health <= 0) {
                    printf("You couldn't get your revenge.  Game over!!!\n");
                    printf("Press any key and enter to exit...");
                    getchar();
                    if (getchar()) {
                        exit(0);
                    }
                }
                if (strcmp(target->name, "Necromancer") == 0 && target->health <= 0) {
                    endGameWithWin();
                }
            } else {
                printf("There is no entity named '%s' here.\n", command + 7);
            }
        }
        else if (strncmp(command, "pickup ", 7) == 0) {
            pickupItem(player, command + 7);
            removeItemFromRoom(player->currentRoom,command + 7);
        }
        else if (strncmp(command, "drop ", 5) == 0) {
            dropItem(player, command + 5);
        }
        else if (strcmp(command, "inventory" ) == 0) {
            displayInventory(player);
        }
        else if (strncmp(command, "player stats", 12) == 0) {
            displayPlayerStats(player);
        }
        else if (strncmp(command, "map", 3) == 0) {
            displayMap();
        }
        else if (strncmp(command, "room info", 9) == 0) {
            displayRoomDescriptions();
        }
        else {
            printf("There is no command named '%s' here.\n", command);
        }
    }
    return 0;
}

