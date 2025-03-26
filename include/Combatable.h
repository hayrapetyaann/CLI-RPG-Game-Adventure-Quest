#ifndef COMBATABLE_H
#define COMBATABLE_H

#include "Character.h"

class ICombatable {
public:
    virtual void attack(Character* target) = 0;
    virtual void useAbility(Character* target) = 0;
};

#endif // COMBATABLE_H