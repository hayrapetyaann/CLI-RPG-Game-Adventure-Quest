#include "NPC.h"

void NPC::displayStats() const {
    std::cout << "Dialogue: " << m_dialogue << std::endl;
    std::cout << "Name: " << m_name << "\nHealth: " << m_health << "\nAttackPower: " << m_attackPower << "Defense: " << m_defense << std::endl;
}

void NPC::takeDamage(int damage) {
    if (damage < 0) return;
    m_health -= damage;
    std::cout << m_name << "takes" << damage << "damage!\n";
}

std::string NPC::getDialogue() const {
    return m_dialogue;
}

void NPC::interact(Character* target) {
    std::cout << m_name << ": " << m_dialogue << "\n";
}

int NPC::getHealth() const  {
    return m_health;
}