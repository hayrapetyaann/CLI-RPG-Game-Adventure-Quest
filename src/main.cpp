#include <iostream>

#include "Hero.h"
#include "GameWorld.h"
#include "QuestManager.h"
#include "Utility.h"

void createHero(Hero*& hero);
void combat(Hero* hero, Monster* monster, QuestManager& qm);

int main() {
    std::cout << "Welcome to Adventure Quest!\n";
    Hero* hero = nullptr;
    GameWorld world;
    QuestManager questManager;
    
    while (true) {
        if (!hero) {
            std::cout << "1. Create Hero\n2. Exit\nChoose an option: ";
            int choice = Utility::getIntInput(1, 2);
            if (choice == 1) {
                createHero(hero);
            } else {
                break;
            }
        } else {
            std::cout << "\nMain Menu:\n1. Explore Location\n2. View Stats\n3. View Inventory\n4. Save Game\n5. Load Game\n6. Exit\nChoose an option: ";
            int choice = Utility::getIntInput(1, 6);
            
            switch (choice) {
                case 1: {
                    std::cout << "\nAvailable Locations:\n1. Enchanted Forest\n2. Dark Dungeon\n3. Quiet Village\nChoose a location: ";
                    int loc = Utility::getIntInput(1, 3);
                    if (loc == 1) {
                        std::cout << "You enter the Enchanted Forest...\nYou encounter a Villager!\n1. Talk to Villager\n2. Ignore\nChoose an action: ";
                        int action = Utility::getIntInput(1, 2);
                        if (action == 1) {
                            world.explore(hero);
                            questManager.addQuest("Retrieve the Stolen Amulet", "Amulet", 50);
                        }
                    } else if (loc == 2) {
                        std::cout << "You enter the Dark Dungeon...\n";
                        Monster* goblin = new Monster("Goblin", 50, 10, 3);
                        goblin->displayStats();
                        combat(hero, goblin, questManager);
                        delete goblin;
                    }
                    break;
                }
                case 2:
                    hero->displayStats();
                    break;
                case 3:
                    std::cout << "Inventory not fully implemented yet!\n";
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
}