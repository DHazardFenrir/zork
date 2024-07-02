#include "World.h"
#include "Entity.h"
#include "Player.h"
#include "Room.h"
#include "Exit.h"
#include "NPC.h"
#include "Human.h"
#include "Monster.h"
#include "Item.h"
#include "globals.h"
#include <vector>
#include <memory>

World::World()
    : tick_timer(clock()) {
    // Constructor is intentionally empty
}

World::~World() {
    // No need for manual cleanup as we are using smart pointers
    entities.clear();
}

void World::Initialize() {
    // Rooms ----
    std::shared_ptr<Room> room1 = std::make_shared<Room>("Room 1", "Description of Room 1");
    std::shared_ptr<Room> room2 = std::make_shared<Room>("Room 2", "Description of Room 2");

    // Exits ----
    std::shared_ptr<Exit> exit1 = std::make_shared<Exit>("Exit 1", "Exit 2", "An exit from Room 1 to Room 2", room1, room2);

    exit1->locked = true;

    entities.push_back(room1);
    entities.push_back(room2);
    entities.push_back(exit1);

    // Define locations
    std::shared_ptr<Room> forest = room1;
    std::shared_ptr<Room> house = room2;

    // NPCs ----
    Stats npcStats{ 5, 5, 5, 5 };
    auto butler = std::make_shared<NPC>("Butler", "The loyal butler.", forest, npcStats);

    entities.push_back(butler);

    // Items -----
    auto mailbox = std::make_shared<Item>("Mailbox", "Looks like it might contain something.", house, ItemType::FOOD, Stats(0, 0, 0, 0));
    auto key = std::make_shared<Item>("Key", "A small key.", forest, ItemType::KEY, Stats{});
    exit1->key = key; // Use exit1 instead of ex2

    auto sword = std::make_shared<Item>("Sword", "A simple old and rusty sword.", forest, ItemType::WEAPON, Stats(0, 3, 1, 0));
    auto shield = std::make_shared<Item>("Shield", "An old wooden shield.", house, ItemType::ARMOUR, Stats(0, 0, 2, 0));

    entities.push_back(mailbox);
    entities.push_back(key);
    entities.push_back(sword);
    entities.push_back(shield);

    // Player ----
    auto player = std::make_shared<Player>("Hero", "The brave hero of our story.", forest, Stats{ 10, 5, 10, 4 });

    player->SetStrength(10); // Adjust as per your game's balance
    entities.push_back(player);
}

bool World::Tick(const vector<string>& args) {
    bool ret = true;

    if (!args.empty() && !args[0].empty()) {
        ret = ParseCommand(args);
    }

    GameLoop();
    return ret;
}

void World::GameLoop() {
    clock_t now = clock();

    if (static_cast<float>(now - tick_timer) / CLOCKS_PER_SEC >= TICK_FREQUENCY) {
        for (const auto& entity : entities) {
            entity->Tick(); // Call the Tick method for each entity
        }

        tick_timer = now;
    }
}

bool World::ParseCommand(const vector<string>& args) {
    bool ret = true;
    // Assuming you have the 'player' object correctly initialized
    std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(entities.back());

    switch (args.size()) {
    case 1: // Commands with no arguments
        if (Same(args[0], "look") || Same(args[0], "l")) {
            player->Look(args);
        }
        else if (Same(args[0], "north") || Same(args[0], "n")) {
            vector<string> new_args = args;
            new_args.push_back("north");
            player->Go(new_args);
        }
        else if (Same(args[0], "south") || Same(args[0], "s")) {
            vector<string> new_args = args;
            new_args.push_back("south");
            player->Go(new_args);
        }
        else if (Same(args[0], "east") || Same(args[0], "e")) {
            vector<string> new_args = args;
            new_args.push_back("east");
            player->Go(new_args);
        }
        else if (Same(args[0], "west") || Same(args[0], "w")) {
            vector<string> new_args = args;
            new_args.push_back("west");
            player->Go(new_args);
        }
        else if (Same(args[0], "up") || Same(args[0], "u")) {
            vector<string> new_args = args;
            new_args.push_back("up");
            player->Go(new_args);
        }
        else if (Same(args[0], "down") || Same(args[0], "d")) {
            vector<string> new_args = args;
            new_args.push_back("down");
            player->Go(new_args);
        }
        else if (Same(args[0], "stats") || Same(args[0], "st")) {
            player->GetDefense();
            player->GetSpeed();
            player->GetStrength();
            player->GetHealth();
        }
        else if (Same(args[0], "inventory") || Same(args[0], "i")) {
            player->Inventory();
        }
        else {
            ret = false;
        }
        break;

    case 2: // Commands with one argument
        if (Same(args[0], "look") || Same(args[0], "l")) {
            player->Look(args);
        }
        else if (Same(args[0], "go")) {
            player->Go(args);
        }
        else if (Same(args[0], "take") || Same(args[0], "pick")) {
            player->Take(args);
        }
        else if (Same(args[0], "drop") || Same(args[0], "put")) {
            player->Drop(args);
        }
        else if (Same(args[0], "equip") || Same(args[0], "eq")) {
            player->Equip(args);
        }
        else if (Same(args[0], "unequip") || Same(args[0], "uneq")) {
            player->UnEquip(args);
        }
        else if (Same(args[0], "attack") || Same(args[0], "at")) {
            player->Attack(args);
        }
        else if (Same(args[0], "loot") || Same(args[0], "lt")) {
            player->Loot(args);
        }
        else if (Same(args[0], "talk")) {
            player->Talk(args);
        }
        else {
            ret = false;
        }
        break;

    case 3: // Commands with two arguments
        break;

    case 4: // Commands with three arguments
        if (Same(args[0], "unlock") || Same(args[0], "unlk")) {
            player->UnLock(args);
        }
        else if (Same(args[0], "lock") || Same(args[0], "lk")) {
            player->Lock(args);
        }
        else if (Same(args[0], "take") || Same(args[0], "pick")) {
            player->Take(args);
        }
        else if (Same(args[0], "drop") || Same(args[0], "put")) {
            player->Drop(args);
        }
        else if (Same(args[0], "eat") || Same(args[0], "et")) {
            player->Eat(args);
        }
        else if (Same(args[0], "drink") || Same(args[0], "drk")) {
            player->Drink(args);
        }
        else {
            ret = false;
        }
        break;

    default:
        ret = false;
    }

    return ret;
}
