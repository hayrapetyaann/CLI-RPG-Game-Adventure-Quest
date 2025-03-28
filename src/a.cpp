#include <iostream>
#include "Hero.h"
#include "GameWorld.h"
#include "QuestManager.h"
#include "Utility.h"
// #include "Horse.h"
#include "Portal.h"

void createHero(Hero*& hero) {
    std::string name;
    std::cout << "Enter hero name: ";
    std::getline(std::cin, name);
    
    std::cout << "Choose hero type (1. Warrior, 2. Mage, 3. Rogue): ";
    int choice = Utility::getIntInput(1, 3);
    
    switch (choice) {
        case 1:
            hero = new Hero(name, 100, 20, 10);
            std::cout << "Hero created: " << name << " the Warrior\n";
            break;
        case 2:
            hero = new Hero(name, 80, 15, 5);
            std::cout << "Hero created: " << name << " the Mage\n";
            break;
        case 3:
            hero = new Hero(name, 90, 18, 7);
            std::cout << "Hero created: " << name << " the Rogue\n";
            break;
    }
    hero->displayStats();
}

void combat(Hero* hero, Monster* monster, QuestManager& qm) {
    while (hero->getHealth() > 0 && monster->getHealth() > 0) {
        std::cout << "\nYour turn:\n1. Attack\n2. Cast Fireball\n3. Defend\n4. Use Potion\nChoose an action: ";
        int choice = Utility::getIntInput(1, 4);
        
        switch (choice) {
            case 1:
                hero->attack(monster);
                break;
            case 2:
                std::cout << hero->getName() << " casts Fireball!\n";
                hero->useAbility(monster);
                break;
            case 3:
                std::cout << "Defending...\n";
                break;
            case 4:
                std::cout << "No potions available!\n";
                break;
        }
        
        if (monster->getHealth() > 0) {
            monster->attack(hero);
        } else {
            std::cout << hero->getName() << " defeats the " << monster->getName() << "! Gained 50 XP and Golden Key.\n";
            hero->gainXP(50);
            std::string item = "Golden Key";
            hero->addItem(item);
            qm.completeQuest(0, hero);
            break;
        }
    }
}

void changeLocation(std::string& currentLocation, Hero* hero, std::vector<Portal>& portals) {
    std::cout << "\nCurrent Location: " << currentLocation << "\n";
    std::cout << "Choose a location:\n";
    std::cout << "1. Village\n";
    std::cout << "2. Forest\n";
    std::cout << "3. Dungeon\n";
    std::cout << "Choose an option (0 to cancel): ";
    int choice = Utility::getIntInput(0, 3);

    Portal* selectedPortal = nullptr;
    switch (choice) {
        case 1:
            selectedPortal = &portals[0];  // Village portal
            break;
        case 2:
            selectedPortal = &portals[1];  // Forest portal
            break;
        case 3:
            selectedPortal = &portals[2];  // Dungeon portal
            break;
        case 0:
            std::cout << "You stay in " << currentLocation << ".\n";
            return;
    }

    if (selectedPortal) {
        if (selectedPortal->isLocked()) {
            std::cout << "Portal Guardian: \"" << selectedPortal->getCondition() << "\"\n";
            if (selectedPortal->isRiddleBased()) {
                std::cout << "Your answer: ";
                std::string answer;
                std::getline(std::cin, answer);
                if (selectedPortal->attemptActivation(answer, hero)) {
                    currentLocation = selectedPortal->getDestination();
                    std::cout << "You travel to " << currentLocation << ".\n";
                }
            } else {
                if (selectedPortal->attemptActivation("", hero)) {
                    currentLocation = selectedPortal->getDestination();
                    std::cout << "You travel to " << currentLocation << ".\n";
                }
            }
        } else {
            currentLocation = selectedPortal->getDestination();
            std::cout << "You travel to " << currentLocation << ".\n";
        }
    }
}

int main() {
    std::cout << "Welcome to Adventure Quest!\n";
    Hero* hero = nullptr;
    GameWorld world;
    QuestManager questManager;
    std::string currentLocation = "Forest";

    // Define portals (simplified for this example)
    std::vector<Portal> portals = {
        Portal("Forest", "Village", true, "What has keys but can't open locks?", "piano"),
        Portal("Forest", "Forest", true, "I speak without a mouth and hear without ears. What am I?", "echo"),
        Portal("Forest", "Dungeon", true, "Golden Key")
    };

    std::cout << "1. Create Hero\n2. Exit\nChoose an option: ";
    int initialChoice = Utility::getIntInput(1, 2);
    if (initialChoice == 1) {
        createHero(hero);
    } else {
        return 0;
    }

    changeLocation(currentLocation, hero, portals);

    std::cout << "Starting the game\n..........\n";
    while (true) {
        std::cout << "\n1. Change location\n2. View Stats\n3. View Inventory\n4. Save Game\n5. Load Game\n6. Exit\n";
        std::cout << "Choose an option: ";
        int choice = Utility::getIntInput(1, 6);
        
        switch (choice) {
            case 1:
                changeLocation(currentLocation, hero, portals);
                break;
            case 2:
                hero->displayStats();
                break;
            case 3:
                hero->displayInventory();
                break;
            case 4:
                Utility::saveGame(hero, "savegame.txt");
                break;
            case 5:
                delete hero;
                hero = Utility::loadGame("savegame.txt");
                break;
            case 6:
                delete hero;
                return 0;
        }
    }

    delete hero;
    return 0;
}