#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <vector>

#include "Hero.h"
#include "Monster.h"
#include "NPC.h"
#include "Portal.h"

class GameWorld {
private:
    std::vector<Character*> m_entities;
    std::vector<Portal*> m_portals;
public:
    GameWorld();
    ~GameWorld();
    void addEntity(Character* entity);
    void addPortal(Portal* portal);
    void explore(Hero* hero);
    const std::vector<Portal*>& getPortals() const;
    const std::vector<Character*>& getEntities() const;
};

#endif // GAMEWORLD_H