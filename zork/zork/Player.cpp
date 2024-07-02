#include <iostream>
#include "Player.h"
#include "Monster.h"
#include "Room.h"

Player::Player(std::string name, Stats stats) : name(name), stats(stats), equippedWeapon(nullptr), equippedShield(nullptr), temporaryDefense(0) {}

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
void Player::inflictStatus(Status status) {
    if (status != Status::None) {
        std::cout << getName() << " is inflicted with ";
        switch (status) {
        case Status::Burn: std::cout << "Burn"; break;
        case Status::Poison: std::cout << "Poison"; break;
        case Status::Paralyze: std::cout << "Paralyze"; break;
        default: break;
        }
        std::cout << "!" << std::endl;
    }
    currentStatus = status;
}

void Player::applyStatusEffects() {
    switch (currentStatus) {
    case Status::Burn:
        stats.setHealth(stats.getHealth() - 5);
        std::cout << getName() << " suffers 5 burn damage!" << std::endl;
        break;
    case Status::Poison:
        stats.setHealth(stats.getHealth() - 10);
        std::cout << getName() << " suffers 10 poison damage!" << std::endl;
        break;
    case Status::Paralyze:
        std::cout << getName() << " is paralyzed and loses a turn!" << std::endl;
        break;
    default:
        break;
    }
}

void Player::cureStatus(Status status) {
    if (currentStatus == status) {
        std::cout << getName() << " is cured of ";
        switch (status) {
        case Status::Burn: std::cout << "Burn"; break;
        case Status::Poison: std::cout << "Poison"; break;
        case Status::Paralyze: std::cout << "Paralyze"; break;
        default: break;
        }
        std::cout << "!" << std::endl;
        currentStatus = Status::None;
    }
}
void Player::useSpecificItem(const Item& item) {
    switch (item.getType()) {
    case ItemType::Potion:  // Assuming ItemType::Potion is for health recovery
        if (stats.getHealth() < stats.getMaxHealth()) {
            stats.setHealth(stats.getHealth() + item.getEffect());
            std::cout << getName() << " uses " << item.getName() << ", restoring " << item.getEffect() << " health points." << std::endl;
            // Cure status if it's a specific cure potion
            if (item.getName() == "Burn Cure Potion") {
                cureStatus(Status::Burn);
            }
            else if (item.getName() == "Poison Cure Potion") {
                cureStatus(Status::Poison);
            }
            else if (item.getName() == "Paralyze Cure Potion") {
                cureStatus(Status::Paralyze);
            }
            removeItem(item.getName());
            break;
        }
        else {
            std::cout << getName() << " can't use " << item.getName() << ", your health is full." << std::endl;
            break;
        }

    case ItemType::Food:  // Food might boost health or provide a temporary stat boost
        stats.setHealth(stats.getDefense() + item.getEffect());
        std::cout << getName() << " eats " << item.getName() << ", gaining " << item.getEffect() << " defense points." << std::endl;
        removeItem(item.getName());
        break;
    default:
        std::cout << item.getName() << " cannot be used right now." << std::endl;
        break;
    }
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
    case ItemType::Potion:
        if (stats.getHealth() < stats.getMaxHealth()) {
            stats.setHealth(stats.getHealth() + item.getEffect());
            std::cout << getName() << " uses " << item.getName() << ", restoring " << item.getEffect() << " health points." << std::endl;
        }
        else {
            std::cout << getName() << " can't use " << item.getName() << ", your health is full" << std::endl;
        }
        break;
    case ItemType::Food:
        stats.setHealth(stats.getHealth() + item.getEffect());
        std::cout << getName() << " eats " << item.getName() << ", gaining " << item.getEffect() << " health points." << std::endl;
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
        useSpecificItem(item);
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
    for (int i = 0; i < itemNames.size(); i++) {
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

bool Player::unlockExit(Room& room, const std::string& direction) {
    for (const auto& item : inventory) {
        std::cout << "Checking item: " << item.getName() << " with effect: " << item.getEffect() << std::endl;
        if (item.getType() == ItemType::Key && room.unlockExit(direction, item)) {
            std::cout << "Key matches! Unlocking exit." << std::endl;
            return true;
        }
    }
    return false;
}
Status Player::getStatus() const {
    return currentStatus;
}

void Player::setStatus(Status status) {
    currentStatus = status;
}




