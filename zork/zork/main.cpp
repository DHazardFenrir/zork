#include <iostream>
#include <string>
#include "Room.h"
#include "Player.h"
#include "Monster.h"
// Function to handle turn-based combat between a player and a monster
void combat(Player& player, Monster& monster) {
    std::string action;
    std::cout << "You have encountered a " << monster.getName() << "! " << monster.getDescription() << "\n";

    while (player.isAlive() && monster.alive()) {
        std::cout << "Your Health: " << player.getStats().getHealth() << ", Monster's Health: " << monster.getStats().getHealth() << "\n";
        std::cout << "Choose action: 'attack' or 'flee' > ";
        std::cin >> action;

        if (action == "flee") {
            std::cout << "You fled from the battle.\n";
            break;
        }
        else if (action == "attack") {
            player.attack(monster);
            if (monster.alive()) {
                monster.attack(player);
            }
            else {
                std::cout << "You have defeated the " << monster.getName() << "!\n";
                break;
            }
        }
        else {
            std::cout << "Invalid action. Choose 'attack' or 'flee'.\n";
            continue;
        }

        if (!player.isAlive()) {
            std::cout << "You have been defeated by the " << monster.getName() << "!\n";
        }
    }
}
int main() {

    // Creating rooms
    Room hall("a grand hall with an echo");
    Room library("a quiet library full of ancient books");
    Room garden("a serene garden with a small pond");
    Room dungeon("a dark dungeon with a foul smell");

    // Connecting rooms
    hall.connect(&library, "north");
    hall.connect(&garden, "east");
    library.connect(&dungeon, "east");

    // Creating and setting a monster in the dungeon
    Stats monsterStats(50, 10, 2);  // Health, Strength, Defense
    Monster goblin("Goblin", "A nasty little goblin with sharp teeth", monsterStats);
    dungeon.setMonster(&goblin);

    // Initialize player
    Stats playerStats(100, 15, 5);  // Health, Strength, Defense
    Player player("Adventurer", playerStats);

    Room* currentRoom = &hall;
    std::string command;

    std::cout << "Welcome to the Adventure Game, " << player.getName() << "!\n";

    while (command != "quit") {
        std::cout << "You are in " << currentRoom->getDescription() << ".\n";
        std::cout << "Available exits: ";
        for (const auto& exit : currentRoom->getExits()) {
            std::cout << exit.first << " ";
        }
        std::cout << "\nWhat do you want to do? ";
        std::cin >> command;

        if (command == "look") {
            currentRoom->describe();
        }
        else if (command == "north" || command == "south" || command == "east" || command == "west") {
            Room* nextRoom = currentRoom->move(command);
            if (nextRoom != currentRoom) {
                currentRoom = nextRoom;
                if (currentRoom->hasMonster()) {
                    combat(player, *currentRoom->getMonster());
                }
            }
        }
        else if (command == "stats") {
         std::cout << "Your Health: " << player.getStats().getHealth() << ", Strength: " << player.getStats().getStrength() << ", Defense: " << player.getStats().getDefense() << "\n";
        }
        else {
            std::cout << "Invalid command. Please try again.\n";
        }

        if (!player.isAlive()) {
            std::cout << "Sadly, your journey ends here, " << player.getName() << ".\n";
            break;
        }
    }

    std::cout << "Thanks for playing!\n";
    return 0;
}

