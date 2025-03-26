#include <iostream>

#include "GameWorld.h"

GameWorld::GameWorld() {
    m_entities.push_back(new NPC("Villager", "A Goblin has stolen my amulet! Please retrieve it."));
    m_entities.push_back(new Monster("Goblin", 50, 10, 3));
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