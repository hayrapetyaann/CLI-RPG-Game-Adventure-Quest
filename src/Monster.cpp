#include <iostream>

#include "Monster.h"

void Monster::displayStats() const {
    std::cout << "Monster: " << m_name << " | m_health: " << m_health << " | Attack: " << m_attackPower << " | Defense: " << m_defense << "\n";
}

void Monster::takeDamage(int damage) {
    int reducedDamage = damage - m_defense;
    m_health -= (reducedDamage > 0) ? reducedDamage : 0;
    std::cout << m_name << " takes " << reducedDamage << " damage!\n";
}

void Monster::attack(Character* target) {
    int damage = m_attackPower - target->getDefense(); 
    std::cout << m_name << " attacks " << target->getName() << " for " << m_attackPower << " damage!\n";
    target->takeDamage(damage);
}

void Monster::useAbility(Character* target) {
    std::cout << m_name << " uses a special ability!\n";
    target->takeDamage(m_attackPower * 1.5);
}

int Monster::getHealth() const {
    return m_health;
}

