#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include "Room.h"
#include "Player.h"
#include "Monster.h"
#include <cstdlib>
#include <ctime>
#include <limits>
#include <vector>

// Function to handle turn-based combat between a player and a monster
void combat(Player& player, Monster& monster) {
    srand(static_cast<unsigned int>(time(NULL)));  // Seed the random number generator

    while (player.isAlive() && monster.alive()) {
        std::cout << "Combat! Your Health: " << player.getStats().getHealth()
            << ", " << monster.getName() << "'s Health: " << monster.getStats().getHealth() << "\n";
        std::cout << "Choose action: 'attack', 'defend', or 'use item': ";
        std::string action;
        std::getline(std::cin, action);  // Use getline to properly read the full input

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
            continue;  // Skip the rest of the loop iteration to prompt again
        }

        // Monster's turn
        if (rand() % 2 == 0) {  // 50% chance to defend
            monster.defend();
        }
        else {
            monster.attack(player);
        }

        // Reset defending status if implemented
        player.resetDefense();  // Reset player defense if necessary
        monster.resetDefense();  // Reset monster defense if necessary

        if (!player.isAlive()) {
            std::cout << "You have been defeated by the " << monster.getName() << "!" << std::endl;
            break;
        }
        else if (!monster.alive()) {
            std::cout << "You have defeated the " << monster.getName() << "!" << std::endl;
            break;
        }

        // Clear the input buffer and reset any error flags in case of bad input
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

int main() {
    // Creating rooms
    Room hall("a grand hall with an echo");
    Room library("a quiet library full of ancient books");
    Room garden("a serene garden with a small pond");
    Room dungeon("a dark dungeon with a foul smell");
    garden.addItem(Item("Old Apple", "A weird looking apple", ItemType::Food, -5));

    // Creating items with nested items
    Item box("Box", "A wooden box", ItemType::Container, 0);
    Item key("Key", "A small key", ItemType::Key, 1);
    box.addItem(key);
    garden.addItem(box);

    // Connecting rooms
    hall.connect(&library, "north");
    hall.connect(&garden, "east");
    library.connect(&dungeon, "east");

    // Creating and setting a monster in the dungeon
    Stats monsterStats(50, 30, 2);  // Health, Strength, Defense
    Monster goblin("Goblin", "A nasty little goblin with sharp teeth", monsterStats);
    Item goblinSword("Rusty Sword", "A dull, rusty old sword.", ItemType::Weapon, 3);
    Item goblinShield("Wooden Shield", "A crude shield made of wood.", ItemType::Shield, 2);

    goblin.equipItem(goblinSword);
    goblin.equipItem(goblinShield);
    dungeon.setMonster(&goblin);

    // Initialize player
    Stats playerStats(100, 15, 5);  // Health, Strength, Defense
    Player player("Adventurer", playerStats);
    Item playerSword("Iron Sword", "A shiny sword made of iron.", ItemType::Weapon, 5);
    Item playerShield("Steel Shield", "A sturdy shield made of steel.", ItemType::Shield, 3);
    player.equipItem(playerSword);
    player.equipItem(playerShield);

    Room* currentRoom = &hall;
    std::string command;

    std::cout << "Welcome to the Adventure Game, " << player.getName() << "!\n";

    while (command != "quit") {
        std::cout << "You are in " << currentRoom->getDescription() << ".\n";
        currentRoom->showItems();
        std::cout << "Available exits: ";
        for (const auto& exit : currentRoom->getExits()) {
            std::cout << exit.first << " ";
        }
        std::cout << "\nWhat do you want to do? ";
        std::getline(std::cin, command);

        std::istringstream iss(command);
        std::vector<std::string> words((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

        if (!words.empty() && words[0] == "look" && words.size() > 2 && words[1] == "at") {
            std::string itemName = words[2];
            for (size_t i = 3; i < words.size(); ++i) {
                itemName += " " + words[i];
            }
            player.lookAtItem(*currentRoom, itemName);
        }
        else if (words[0] == "east" || words[0] == "west" || words[0] == "north" || words[0] == "south") {
            Room* nextRoom = currentRoom->move(words[0]);
            if (nextRoom != nullptr) {
                currentRoom = nextRoom;
                if (currentRoom->hasMonster()) {
                    combat(player, *currentRoom->getMonster());
                }
            }
            else {
                std::cout << "You can't go that way.\n";
            }
        }
        else if (words[0] == "pick up") {
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
        else if (words[0] == "inventory") {
            player.showInventory();
        }
        else {
            std::cout << "Invalid command. Please try again.\n";
        }

        // Clear any residual data in the input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Thanks for playing!\n";
    return 0;
}
