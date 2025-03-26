#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include "Character.h"

class IInteractable {
public:
    virtual void interact(Character* target) = 0;
    virtual std::string getDialogue() const = 0;
};

#endif // INTERACTABLE_H