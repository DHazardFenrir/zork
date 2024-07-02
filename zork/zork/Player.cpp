#include <iostream>
#include "Player.h"
#include "Monster.h"
#include "Room.h"

Player::Player(std::string name, Stats stats) : name(name), stats(stats) {}

void Player::attack(Monster& target) {
    int damage = stats.getStrength() - target.getStats().getDefense();
    if (damage < 0) damage = 0;
    std::cout << name << " attacks " << target.getName() << " for " << damage << " damage!\n";
    target.takeDamage(damage);
}

void Player::lookAtItem(Room& room, const std::string& itemName) {
    Item* item = room.getItem(itemName);

    if (item) {
        std::cout << "You look at the " << item->getName() << ": " << item->getDescription() << std::endl;
        if (!item->getContents().empty()) {
            std::cout << "It contains:" << std::endl;
            for (const auto& containedItem : item->getContents()) {
                std::cout << "- " << containedItem.getName() << std::endl;
                addItem(containedItem);  // Add contained item to player's inventory
            }
            item->getMutableContents().clear();  // Clear the contents after taking them
        }
        addItem(*item);
        room.removeItem(item->getName());
        std::cout << item->getName() << " has been picked up from the room." << std::endl;
    }
    else {
        std::cout << "There is no " << itemName << " here." << std::endl;
    }
}

void Player::takeDamage(int damage) {
    int effectiveDefense = stats.getDefense() + temporaryDefense;
    int netDamage = damage - effectiveDefense;
    if (netDamage < 0) netDamage = 0;
    std::cout << getName() << " takes " << netDamage << " damage!" << std::endl;
    stats.setHealth(stats.getHealth() - netDamage);
}

std::string Player::getName() const {
    return name;
}

bool Player::isAlive() const {
    return stats.getHealth() > 0;
}

const Stats& Player::getStats() const {
    return stats;
}

void Player::equipItem(const Item& item) {
    switch (item.getType()) {
    case ItemType::Weapon:
        equippedWeapon = &item;
        stats.setStrength(stats.getStrength() + item.getEffect());
        break;
    case ItemType::Shield:
        equippedShield = &item;
        stats.setDefense(stats.getDefense() + item.getEffect());
        break;
    default:
        std::cout << "Item cannot be equipped.\n";
        break;
    }
}

void Player::useItem(const Item& item) {
    switch (item.getType()) {
    case ItemType::Potion:  // Assuming ItemType::Potion is for health recovery
        if (stats.getHealth() < stats.getMaxHealth()) {
            stats.setHealth(stats.getHealth() + item.getEffect());
            std::cout << getName() << " uses " << item.getName() << ", restoring " << item.getEffect() << " health points." << std::endl;
            break;
        }
        else {
            std::cout << getName() << " can't use " << item.getName() << ", your health is full" << std::endl;
            break;
        }
    case ItemType::Food:  // Food might boost health or provide a temporary stat boost
        stats.setHealth(stats.getDefense() + item.getEffect());
        std::cout << getName() << " eats " << item.getName() << ", gaining " << item.getEffect() << " defense points." << std::endl;
        break;
    default:
        std::cout << item.getName() << " cannot be used right now." << std::endl;
        break;
    }
}

void Player::defend() {
    int defenseBoost = equippedShield ? equippedShield->getEffect() + 15 : 15;
    temporaryDefense += defenseBoost;
    std::cout << getName() << " is defending and increases defense by " << defenseBoost << "." << std::endl;
}

void Player::resetDefense() {
    temporaryDefense = 0; // Reset any temporary defense boosts
    std::cout << getName() << " defense reset to normal." << std::endl;
}

void Player::addItem(const Item& item) {
    inventory.push_back(item);
    std::cout << item.getName() << " added to inventory." << std::endl;
}

bool Player::removeItem(const std::string& itemName) {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if (it->getName() == itemName) {
            inventory.erase(it);
            std::cout << itemName << " removed from inventory." << std::endl;
            return true;
        }
    }
    std::cout << itemName << " not found in inventory." << std::endl;
    return false;
}

void Player::useItem() {
    showInventory();
    if (inventory.empty()) {
        return;
    }
    std::cout << "Enter the number of the item to use: ";
    int index;
    std::cin >> index;
    if (index > 0 && index <= inventory.size()) {
        Item& item = inventory[index - 1];
        if (item.getType() == ItemType::Potion || item.getType() == ItemType::Food) {
            useItem(item);
        }
        else {
            std::cout << item.getName() << " is not usable in combat." << std::endl;
        }
    }
    else {
        std::cout << "Invalid item selection." << std::endl;
    }
}

void Player::showInventory() const {
    if (inventory.empty()) {
        std::cout << "Inventory is empty." << std::endl;
        return;
    }
    std::cout << "Inventory:" << std::endl;
    for (size_t i = 0; i < inventory.size(); ++i) {
        std::cout << i + 1 << ". " << inventory[i].getName() << " - " << inventory[i].getDescription() << std::endl;
    }
}

void Player::pickUpItem(Room& room) {
    std::vector<std::string> itemNames = room.getItemNames();
    if (itemNames.empty()) {
        std::cout << "There are no items to pick up in this room." << std::endl;
        return;
    }

    std::cout << "Items available to pick up:" << std::endl;
    for (size_t i = 0; i < itemNames.size(); i++) {
        std::cout << i + 1 << ": " << itemNames[i] << std::endl;
    }

    std::cout << "Select an item number to pick up: ";
    int choice;
    std::cin >> choice;
    if (choice > 0 && choice <= itemNames.size()) {
        Item* item = room.getItem(itemNames[choice - 1]);
        if (item) {
            addItem(*item);  // Add item to player's inventory
            room.removeItem(item->getName());  // Remove item from room
        }
        else {
            std::cout << "Item not found." << std::endl;
        }
    }
    else {
        std::cout << "Invalid selection." << std::endl;
    }
}

Item* Player::findItemInInventory(const std::string& itemName) {
    for (auto& item : inventory) {
        if (item.getName() == itemName) {
            return &item;
        }
    }
    return nullptr;
}
