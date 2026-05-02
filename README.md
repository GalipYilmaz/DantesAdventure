# Dante's Adventure

## Description

Dante's Adventure is a text-based dungeon crawler game where the player explores rooms, collects items, and manages an inventory with various effects. 
The game features equipment that can affect the player's stats like strength, health, and inventory capacity. Players can pick up and drop items, and the game reacts accordingly based on the items in their possession.

## Features

- **Player and Inventory System**: The player has an inventory that can store items. Inventory capacity is limited, and items can be picked up or dropped.
- **Items and Equipment**: There are several items that affect the player's stats. These include:
 - **Healing Potions**: Increase health when picked up.
  - **Weapons and Armor**: Increase strength or health when equipped.
- **Dungeon Exploration**: The player can move through rooms and interact with items.

## Project Structure
The project consists of several C files and headers that define the different components of the game:

main.c
Player.h
Player.c
Inventory.h
Item.h
Item.c
Room.h
Room.c
Entity.h
Entity.c

### Files

- **main.c**: Contains the main game loop, where the player can interact with the game world.
- **Player.c / Player.h**: Defines the player and their attributes, including inventory.
- **Item.c / Item.h**: Defines the different items and their effects.
- **Room.c / Room.h**: Manages room logic and player movement.
- **Entity.c / Entity.h**: Defines any non-player entities in the dungeon.
  
### Game Mechanics

The game revolves around the following mechanics:
1. Movement
Player can move up,down,left,right. (e.g. move up)
2. Look
Player can look at what is happening around him. (e.g. look)
3. Attack
Player can attack the entities. (e.g. attack Spider)
4. Pickup
Player can pick items from rooms. (e.g. pickup Dead Man's Bag)
5. Drop
Player can drop items from inventory. (e.g. drop Daed Man's Bag)
6.Player Stats
Player can see his health, strength, and inventory capacity. (e.g. player stats)
7. Map
Player can see The Map of the Mountain. (e.g. map)
8.Room Info
Player can see Room infos. (e.g. room info)
9.Exit
Player can exit from the game. (e.g. exit)

### Contact
For questions or suggestions, feel free to reach out to [galip.ylmz71@hotmail.com].
