#include <iostream>
#include <string>
#include <sstream>
#include "Room.h"
#include "Player.h"
#include "Monster.h"
#include "Status.h"
#include <cstdlib>
#include <ctime>
#include <limits>
#include <vector>

bool combat(Player& player, Monster& monster) {
    srand(time(NULL));

    while (player.isAlive() && monster.alive()) {
        player.applyStatusEffects(); // Apply status effects at the start of each turn

        std::cout << "Combat! Your Health: " << player.getStats().getHealth()
            << ", " << monster.getName() << "'s Health: " << monster.getStats().getHealth() << "\n";
        std::cout << "Choose action: 'attack', 'defend', or 'use item': ";
        std::string action;
        std::getline(std::cin, action);

        if (action == "defend") {
            player.defend();
        }
        else if (action == "attack") {
            player.attack(monster);
        }
        else if (action == "use item") {
            player.useItem();
        }
        else {
            std::cout << "Invalid command. Please choose 'attack', 'defend', or 'use item'.\n";
            continue;
        }

        if (player.getStatus() != Status::Paralyze) {
            if (rand() % 2 == 0) {
                monster.defend();
            }
            else {
                monster.attack(player);
            }
        }
        else {
            std::cout << "Player is paralyzed and loses a turn!" << std::endl;
            player.setStatus(Status::None); // Paralysis only lasts one turn
        }

        player.resetDefense();
        monster.resetDefense();

        if (!player.isAlive()) {
            std::cout << "You have been defeated by the " << monster.getName() << "!" << std::endl;
            return false;
        }
        else if (!monster.alive()) {
            std::cout << "You have defeated the " << monster.getName() << "!" << std::endl;
            return true;
        }

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return false;
}

int main() {
    Room hall("a grand hall with an echo");
    Room library("a quiet library full of ancient books");
    Room garden("a serene garden with a small pond");
    Room dungeon("a dark dungeon with a foul smell");
    garden.addItem(Item("Old Apple", "A weird looking apple", ItemType::Food, -5));
    library.addItem(Item("Burn Cure Potion", "A glowing potion", ItemType::Potion, 10));
    hall.addItem(Item("Poison Cure Potion", "A potion to cure poisoning", ItemType::Potion, 15));
    hall.addItem(Item("Health Potion", "A potion to restore health", ItemType::Potion, 20));
    Item box("Box", "A wooden box", ItemType::Container, 0);
    Item key("Key", "A small key", ItemType::Key, 1);
    box.addItem(key);
    garden.addItem(box);

    hall.connect(&library, "north");
    hall.connect(&garden, "east");
    library.connect(&dungeon, "east");

    library.setLockedExit("east", 1);

    Stats monsterStats(50, 30, 2);
    Monster goblin("Goblin", "A nasty little goblin with sharp teeth", monsterStats);
    Item goblinSword("Rusty Sword", "A dull, rusty old sword.", ItemType::Weapon, 3);
    Item goblinShield("Wooden Shield", "A crude shield made of wood.", ItemType::Shield, 2);

    goblin.equipItem(goblinSword);
    goblin.equipItem(goblinShield);
    dungeon.setMonster(&goblin);

    Stats playerStats(100, 15, 5);
    Player player("Adventurer", playerStats);
    Item playerSword("Iron Sword", "A shiny sword made of iron.", ItemType::Weapon, 5);
    Item playerShield("Steel Shield", "A sturdy shield made of steel.", ItemType::Shield, 3);
    player.equipItem(playerSword);
    player.equipItem(playerShield);

    Room* currentRoom = &hall;
    std::string command;
    bool gameOver = false;

    std::cout << "Welcome to a copy of Zork!, " << player.getName() << "!\n";

    while (command != "quit" && !gameOver) {
        player.applyStatusEffects(); // Apply status effects outside of combat

        std::cout << "You are in " << currentRoom->getDescription() << ".\n";
        currentRoom->showItems();
        std::cout << "Available exits: ";
        for (const auto& exit : currentRoom->getExits()) {
            std::cout << exit.first << " ";
            if (currentRoom->isExitLocked(exit.first)) {
                std::cout << "(locked) ";
            }
        }
        std::cout << "\nWhat do you want to do? ";
        std::getline(std::cin, command);

        std::istringstream iss(command);
        std::vector<std::string> words((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

        if (!words.empty() && words[0] == "look" && words.size() > 2 && words[1] == "at") {
            std::string itemName = words[2];
            for (int i = 3; i < words.size(); ++i) {
                itemName += " " + words[i];
            }
            player.lookAtItem(*currentRoom, itemName);
        }
        else if (words[0] == "east" || words[0] == "west" || words[0] == "north" || words[0] == "south") {
            Room* nextRoom = currentRoom->move(words[0]);
            if (nextRoom != nullptr) {
                currentRoom = nextRoom;
                if (currentRoom->hasMonster()) {
                    gameOver = combat(player, *currentRoom->getMonster());
                    if (gameOver) {
                        std::cout << "Congratulations! You have completed the game by defeating the goblin!" << std::endl;
                        break;
                    }
                }
            }
            else {
                std::cout << "You can't go that way.\n";
            }
        }
        else if (words[0] == "unlock" && words.size() == 2) {
            if (player.unlockExit(*currentRoom, words[1])) {
                std::cout << "The " << words[1] << " exit has been unlocked.\n";
            }
            else {
                std::cout << "You can't unlock the " << words[1] << " exit.\n";
            }
        }
        else if (words[0] == "pick" && words.size() > 1 && words[1] == "up") {
            if (!currentRoom->getItems().empty()) {
                player.pickUpItem(*currentRoom);
            }
            else {
                std::cout << "There are no items to pick up here.\n";
            }
        }
        else if (words[0] == "stats") {
            std::cout << "Your Health: " << player.getStats().getHealth()
                << ", Strength: " << player.getStats().getStrength()
                << ", Defense: " << player.getStats().getDefense() << "\n";
        }
        else {
            std::cout << "Invalid command. Please try again.\n";
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Thanks for playing!\n";
    return 0;
}
