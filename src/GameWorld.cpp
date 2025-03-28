#include <iostream>

#include "GameWorld.h"

GameWorld::GameWorld() {
    m_entities.push_back(new NPC("Villager", "A Goblin has stolen my amulet! Please retrieve it."));
    m_entities.push_back(new Monster("Goblin", 50, 10, 3));
    m_portals.push_back(new Portal("Enchanted Forest", "Village", true, "What has keys but can't open locks?", "piano"));
    m_portals.push_back(new Portal("Enchanted Forest", "Dungeon", true, "I speak without a mouth and hear without ears. What am I?", "echo"));
    m_portals.push_back(new Portal("Village", "Enchanted Forest", true, "What has a head, a tail, but no body?", "coin"));
    m_portals.push_back(new Portal("Dungeon", "Enchanted Forest", false, ""));  
}

GameWorld::~GameWorld() {
    for (auto entity : m_entities) {
        delete entity;
    }
}

void GameWorld::addEntity(Character* entity) {
    m_entities.push_back(entity);
}

void GameWorld::explore(Hero* hero) {
    std::cout << "Exploring the world...\n";
    for (auto entity : m_entities) {
        entity->displayStats();
    }
}

void GameWorld::addPortal(Portal* portal) {
    m_portals.push_back(portal);
}

const std::vector<Portal*>& GameWorld::getPortals() const {
    return m_portals;
}

const std::vector<Character*>& GameWorld::getEntities() const {
    return m_entities;
}
