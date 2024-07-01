#include <iostream>
#include "Room.h"
#include "Exit.h"
#include "Item.h"
#include "Monster.h"

using namespace std;

Room::~Room()
{
}

void Room::AddItem(shared_ptr<Item> item) {
    items.push_back(item);
}

void Room::AddEntity(shared_ptr<Entity> entity) {
    entities.push_back(entity);
}

void Room::Look() const
{
    // Print room name and description
    cout << "\n" << name << "\n";
    cout << description;

    // Iterate through entities to find exits and monsters
    for (const auto& entity : entities) {
        // Handle exits
        if (entity->GetType() == EntityType::EXIT) {
            auto ex = std::static_pointer_cast<Exit>(entity);  // Use static_pointer_cast instead
            if (ex) {
                auto destinationRoom = ex->GetDestinationFrom(shared_ptr<Room>(const_cast<Room*>(this)));  // Use a shared_ptr<Room> here
                if (destinationRoom) {
                    cout << "\nDirection (" << ex->GetNameFrom(shared_ptr<Room>(const_cast<Room*>(this))) << ") you see " << destinationRoom->GetName();
                }
            }
        }
    }

    // Iterate through items to print their names
    for (const auto& item : items) {
        cout << "\nThere is an item here: " << item->GetName();
    }

    // Iterate through entities to find monsters
    for (const auto& entity : entities) {
        if (entity->GetType() == EntityType::MONSTER) {
            auto monster = std::static_pointer_cast<Monster>(entity);
            if (monster) {
                cout << "\nThere is someone else here: " << monster->GetName();
                if (!monster->IsAlive()) {
                    cout << " (dead)";
                }
            }
        }
    }

    cout << "\n";
}

shared_ptr<Exit> Room::GetExit(const string& direction) const
{
    for (const auto& entity : entities) {
        if (entity->GetType() == EntityType::EXIT) {
            auto ex = std::static_pointer_cast<Exit>(entity);  // Use static_pointer_cast instead
            if (ex && ex->GetNameFrom(shared_ptr<Room>(const_cast<Room*>(this))) == direction) {  // Use a shared_ptr<Room> here
                return ex;
            }
        }
    }

    return nullptr;
}

EntityType Room::GetType() const {
    return EntityType::ROOM;
}
