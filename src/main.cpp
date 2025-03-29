#include <iostream>
#include "Hero.h"
#include "GameWorld.h"
#include "QuestManager.h"
#include "Utility.h"

void createHero(Hero*& hero);
void combat(Hero* hero, Monster* monster, QuestManager& qm);
void changeLocation(std::string& currentLocation, Hero* hero, GameWorld& world);

int main() {
    std::cout << "Welcome to Adventure Quest!\n";
    Hero* hero = nullptr;
    GameWorld world;
    QuestManager questManager;
    std::string currentLocation = "Enchanted Forest";

    std::cout << "Starting the game\n..........\n";
    while (true) {
        if (!hero) {
            std::cout << "1. Create Hero\n2. Exit\nChoose an option: ";
            int choice = Utility::getIntInput(1, 2);
            if (choice == 1) {
                createHero(hero);
                changeLocation(currentLocation, hero, world);  
            } else {
                break;
            }
        } else {
            std::cout << "\nCurrent Location: " << currentLocation << "\n";
            std::cout << "1. Change location\n2. Start attacking\n3. View Stats\n4. View Inventory\n5. Save Game\n6. Load Game\n7. Interact with NPC\n8. Exit\n";
            std::cout << "Choose an option: ";
            int choice = Utility::getIntInput(1, 8);

            switch (choice) {
                case 1:
                    changeLocation(currentLocation, hero, world);
                    break;
                case 2: {
                    Monster* goblin = new Monster("Goblin", 50, 10, 3);
                    combat(hero, goblin, questManager);
                    delete goblin;
                    break;
                }
                case 3:
                    hero->displayStats();
                    break;
                case 4:
                    hero->displayInventory();
                    break;
                case 5:
                    Utility::saveGame(hero, "savegame.txt");
                    break;
                case 6:
                    delete hero;
                    hero = Utility::loadGame("savegame.txt");
                    break;
                case 7: {
                    const std::vector<Character*>& entities = world.getEntities();
                    for (auto* entity : entities) {
                        if (NPC* npc = dynamic_cast<NPC*>(entity)) {
                            hero->interact(npc);
                            break; 
                        }
                    }
                    break;
                }
                case 8:
                    delete hero;
                    return 0;
            }
        }
    }

    delete hero;
    return 0;
}

void createHero(Hero*& hero) {
    std::string name;
    std::cout << "Enter hero name: ";
    std::getline(std::cin, name);
    
    std::cout << "Choose hero type (1. Warrior, 2. Mage, 3. Rogue): ";
    int choice = Utility::getIntInput(1, 3);
    
    switch (choice) {
        case 1: 
            hero = new Hero(name, 100, 20, 10);
            std::cout << "\033[32mHero created: " << name << " the Warrior\033[0m\n";
            break;
        case 2:
            hero = new Hero(name, 80, 15, 5);
            std::cout << "\033[32mHero created: " << name << " the Mage\033[0m\n";
            break;
        case 3: 
            hero = new Hero(name, 90, 18, 7);
            std::cout << "\033[32mHero created: " << name << " the Rogue\033[0m\n";
            break;
    }
    hero->displayStats();
}

void combat(Hero* hero, Monster* monster, QuestManager& qm) {
    std::cout << "A " << monster->getName() << " appears in your path!\n";
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
            std::cout << hero->getName() << " defeats the " << monster->getName() << "! Gained 20 XP and Stolen Amulet.\n";
            hero->gainXP(20);
            std::string item = "Stolen Amulet";
            hero->addItem(item);
            qm.completeQuest(0, hero);
            break;
        }
    }
    if (hero->getHealth() <= 0) {
        std::cout << "You have been defeated! Game Over.\n";
        exit(0);
    }
}

void changeLocation(std::string& currentLocation, Hero* hero, GameWorld& world) {
    std::cout << "\nCurrent Location: " << currentLocation << "\n";
    std::cout << "Available portals:\n";

    const std::vector<Portal*>& portals = world.getPortals();
    int validPortals = 0;
    for (size_t i = 0; i < portals.size(); ++i) {
        if (portals[i]->getSource() == currentLocation) {
            std::cout << validPortals + 1 << ". To " << portals[i]->getDestination()
                      << (portals[i]->isLocked() ? " (Locked)" : "") << "\n";
            validPortals++;
        }
    }
    if (validPortals == 0) {
        std::cout << "No portals available from here!\n";
        return;
    }

    std::cout << "Choose a portal (0 to cancel): ";
    int choice = Utility::getIntInput(0, validPortals);
    if (choice == 0) {
        std::cout << "You stay in " << currentLocation << ".\n";
        return;
    }

    int portalIndex = -1;
    int count = 0;
    for (size_t i = 0; i < portals.size(); ++i) {
        if (portals[i]->getSource() == currentLocation) {
            count++;
            if (count == choice) {
                portalIndex = i;
                break;
            }
        }
    }

    Portal* selectedPortal = portals[portalIndex];
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
