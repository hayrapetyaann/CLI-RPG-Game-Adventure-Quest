#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <vector>

#include "Hero.h"
#include "Monster.h"
#include "NPC.h"

class GameWorld {
private:
    std::vector<Character*> m_entities;
public:
    GameWorld();
    ~GameWorld();
    void addEntity(Character* entity);
    void explore(Hero* hero);
};

#endif // GAMEWORLD_H