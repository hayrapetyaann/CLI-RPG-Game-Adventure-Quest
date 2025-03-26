#include <iostream>
#include <fstream>

#include "Utility.h"

namespace Utility {
    int getIntInput(int min, int max) {
        int input;
        while (true) {
            std::cin >> input;
            if (std::cin.fail() || input < min || input > max) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Please enter a number between " << min << " and " << max << ": ";
            } else {
                std::cin.ignore(10000, '\n');
                return input;
            }
        }
    }

    void saveGame(const Hero* hero, const std::string& filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << hero->getName() << "\n";
            file << hero->getLevel() << "\n";
            file << hero->getXP() << "\n";
            file.close();
            std::cout << "Game saved successfully!\n";
        } else {
            std::cout << "Error saving game!\n";
        }
    }

    Hero* loadGame(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string name;
            int level, xp;
            std::getline(file, name);
            file >> level >> xp;
            file.close();
            
            Hero* hero = new Hero(name, 80, 15, 5); 
            for (int i = 1; i < level; i++) {
                hero->gainXP(100); 
            }
            hero->gainXP(xp);
            std::cout << "Game loaded successfully!\n";
            return hero;
        }
        std::cout << "Error loading game!\n";
        return nullptr;
    }
}