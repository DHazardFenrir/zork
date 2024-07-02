#include <iostream>
#include "Player.h"
#include "Monster.h"  // This must be included here to fully define Monster


Player::Player(std::string name, Stats stats) : name(name), stats(stats) {}

void Player::attack(Monster& target) {
    int damage = stats.getStrength() - target.getStats().getDefense();
    if (damage < 0) damage = 0;
    std::cout << name << " attacks " << target.getName() << " for " << damage << " damage!\n";
    target.takeDamage(damage);
}

void Player::takeDamage(int damage) {
    int netDamage = damage - stats.getDefense();
    if (netDamage < 0) netDamage = 0;
    std::cout<<name<<" takes "<<netDamage<<" damage!\n";
    stats.takeDamage(netDamage);
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
    // Implement logic based on item type, e.g., healing potions, food
}
