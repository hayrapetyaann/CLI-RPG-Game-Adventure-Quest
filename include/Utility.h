#ifndef UTILITY_H
#define UTILITY_H

#include <string>

#include "Hero.h"

namespace Utility {
    int getIntInput(int min, int max);
    void saveGame(const Hero* hero, const std::string& filename);
    Hero* loadGame(const std::string& filename);
}

#endif // UTILITY_H