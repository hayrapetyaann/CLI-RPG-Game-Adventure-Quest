#ifndef HERO_H
#define HERO_H

#include <vector>
#include <iostream>

#include "Character.h"
#include "Interactable.h"
#include "Combatable.h"
#include "NPC.h"

class Hero : public Character, public IInteractable, public ICombatable {
private:
    int m_level;
    int m_experience;
    std::vector<std::string> m_inventory;
public: 
    Hero(const std::string& n, int h, int a, int d)
        : Character(n, h, a, d), m_level(1), m_experience(0) {}
    void displayStats() const override;
    void takeDamage(int damage) override;
    void attack(Character* target) override;
    void useAbility(Character* target) override;
    void interact(Character* target) override;
    std::string getDialogue() const override;
    int getHealth() const override;
    void addItem(std::string& item);
    void gainXP(int xp);
    int getLevel() const;
    int getXP() const;
};

#endif // HERO_H