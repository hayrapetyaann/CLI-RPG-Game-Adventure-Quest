#include "Hero.h"


void Hero::displayStats() const {
    std::cout << "Hero: " << m_name << "\nHealth: " << m_health << "\nAttack: " << m_attackPower << "\nDefense: " << m_defense << "\nLevel: " << m_level << "\n";
}

void Hero::takeDamage(int damage) {
    if (damage < 0) {
        return;
    }
    int reducedDamage = damage - m_defense;
    m_health -= (reducedDamage > 0) ? reducedDamage : 0;
    if (m_health <= 0) {
        std::cout << "game over! try again... \n";
    }
    std::cout << m_name << "takes" << reducedDamage << "damage!\n";
}

void Hero::attack(Character* target) {
    if (!target) {
        return;
    }
    std::cout << m_name << "attacks. " << target->getName() << "for" << m_attackPower << "damage!\n";
    target->takeDamage(m_attackPower);
}

void Hero::useAbility(Character* target) {
    std::cout << m_name << "uses a powerful ability!\n";
    target->takeDamage(m_attackPower * 2);
}

void Hero::addItem(std::string& item) {
    m_inventory.push_back(item);
    std::cout << item << "succesfully added to inventory.\n";
}

void Hero::interact(Character* target) {
    if (!target) {
        return;
    }

    if (NPC* npc = dynamic_cast<NPC*>(target)) {
        npc->interact(this); 
    }
} 

int Hero::getHealth() const {
    return m_health;
}

std::string Hero::getDialogue() const {
    return "I am " + m_name + ", here to help!";
}

void Hero::gainXP(int xp) {
    m_experience += xp;
    std::cout << m_name << "gained" << xp << " XP!\n";
}

int Hero::getLevel() const {
    return m_level;
}

int Hero::getXP() const {
    return m_experience;
}