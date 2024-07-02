#include "Room.h"
#include <iostream>

Room::Room(std::string desc) : description(desc), monster(nullptr) {}

void Room::connect(Room* room, const std::string& direction) {
    exits[direction] = room;
    // Define the opposite direction for the bidirectional connection
    std::string oppositeDirection = direction == "north" ? "south" :
        direction == "south" ? "north" :
        direction == "east" ? "west" :
        direction == "west" ? "east": "";
    room->exits[oppositeDirection] = this;
}

void Room::addItem(const Item& item) {
    items.push_back(item);
   
}

void Room::removeItem(const std::string& itemName) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->getName() == itemName) {
            std::cout << it->getName() << " has been picked up from the room." << std::endl;
            items.erase(it);
            return;
        }
    }
}

void Room::showItems() const {
    if (items.empty()) {
        std::cout << "No items to see here." << std::endl;
        return;
    }
    std::cout << "Items in this room:" << std::endl;
    for (const auto& item : items) {
        std::cout << " - " << item.getName() << ": " << item.getDescription() << std::endl;
    }
}

std::vector<Item>& Room::getItems() {
    return items;
}

void Room::setMonster(Monster* m) {
    monster = m;
}

bool Room::hasMonster() const {
    return monster != nullptr;
}

Monster* Room::getMonster() const {
    return monster;
}

std::string Room::getDescription() const {
    return description;
}

const std::map<std::string, Room*>& Room::getExits() const {
    return exits;
}

void Room::describe() const {
    std::cout << "You are in " << description << ".\n";
    if (!items.empty()) {
        std::cout << "You see: ";
        for (const Item& item : items) {
            std::cout << item.getName() << " (" << item.getDescription() << "), ";
        }
        std::cout << "\b\b. \n"; // Remove last comma and add period
    }
    if (monster && monster->alive()) {
        std::cout << "There is a " << monster->getName() << " here! " << monster->getDescription() << "\n";
    }
    std::cout << "Exits: ";
    for (auto exit : exits) {
        std::cout << exit.first << " ";
    }
    std::cout << std::endl;
}

Room* Room::move(const std::string& direction) {
    if (exits.find(direction) != exits.end()) {
        return exits[direction];
    }
    else {
        std::cout << "You can't go that way.\n";
        return this;
    }
}

std::vector<std::string> Room::getItemNames() const {
    std::vector<std::string> names;
    for (const Item& item : items) {
        names.push_back(item.getName());
    }
    return names;
}

Item* Room::getItem(const std::string& itemName) {
    for (Item& item : items) {
        if (item.getName() == itemName) {
            return &item;
        }
    }
    return nullptr; // Return nullptr if no item matches
}

void Room::setLockedExit(const std::string& direction, int lockId) {
    lockedExits[direction] = true;
    lockIds[direction] = lockId;
}

bool Room::unlockExit(const std::string& direction, const Item& key) {
    if (lockedExits[direction] && key.getEffect() == lockIds[direction]) {
        lockedExits[direction] = false;
        std::cout << "You unlock the " << direction << " exit." << std::endl;
        return true;
    }
    return false;
}
