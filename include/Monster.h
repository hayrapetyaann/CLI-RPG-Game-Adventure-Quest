#ifndef MONSTER_H
#define MONSTER_H

#include "Character.h"
#include "Combatable.h"

class Monster : public Character, public ICombatable {
public:
    Monster(const std::string& n, int h, int a, int d) : Character(n, h, a, d) {}
    void displayStats() const override;
    void takeDamage(int damage) override;
    void attack(Character* target) override;
    void useAbility(Character* target) override;
    int getHealth() const override;
};

#endif // MONSTER_H