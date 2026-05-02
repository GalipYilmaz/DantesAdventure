#ifndef ENTITIY_H
#define ENTITIY_H


typedef struct {
    char* name;
    int health;
    int strength;
} Entity;

Entity* createEntity(const char* name, int health, int strength);
Entity* createPresetEntity(int type);
void entityTakeDamage(Entity* entity, int damage);
void displayEntityStats(Entity* entity);
void destroyEntity(Entity* entity);

typedef enum {
    ORC,
    GOLEM,
    NECROMANCER,
    UNDEAD,
    SPIDER,
    DANTE,
} EntityType;

#endif //ENTITIY_H
