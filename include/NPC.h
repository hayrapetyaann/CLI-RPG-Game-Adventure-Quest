#ifndef NPC_H
#define NPC_H

#include <iostream>

#include "Character.h"
#include "Interactable.h"

class NPC : public Character, public IInteractable {
private:
    std::string m_dialogue;
public:
    NPC(const std::string& n, const std::string& d) : Character(n, 100, 0, 0), m_dialogue(d) {}
    void displayStats() const override;
    void takeDamage(int damage) override;
    std::string getDialogue() const override;
    void interact(Character* target) override;
    int getHealth() const override;
};

#endif // NPC_H