#include "Entity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Preset entities (Orcs, Golems, etc.)
static const struct {
    const char* name;
    int health;
    int strength;
} presetEntities[] = {
    {"Orc", 100, 30},
    {"Golem", 150, 60},
    {"Necromancer", 500, 100},
    {"Undead", 50, 20},
    {"Spider", 30, 15}
};

// Create a new entity
Entity* createEntity(const char* name, int health, int strength) {
    Entity* entity = malloc(sizeof(Entity));
    if (!entity) return NULL;
    entity->name = strdup(name);
    entity->health = health;
    entity->strength = strength;

    return entity;
}

// Create a preset entity
Entity* createPresetEntity(int type) {
    return createEntity(
        presetEntities[type].name,
        presetEntities[type].health,
        presetEntities[type].strength
    );
}

// Destroy an entity
void destroyEntity(Entity* entity) {
    if (!entity) return;
    free(entity->name);
    free(entity);

}

// Inflict damage to an entity
void entityTakeDamage(Entity* entity, int damage) {
    if (!entity) return;

    if (entity->health > damage) {
        entity->health -= damage;
    } else {
        entity->health = 0;
        printf("%s has died!\n", entity->name);
        printf("\n");
    }
}


// Display the stats of an entity
void displayEntityStats(Entity* entity) {
    if (!entity) return;
    printf("Name: %s\n", entity->name);
    printf("Health: %d\n", entity->health);
    printf("Strength: %d\n", entity->strength);
}
