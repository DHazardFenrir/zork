#include "Monster.h"
#include "Player.h"
#include <iostream>

Monster::Monster(std::string name, std::string description, Stats stats)
    : name(name), description(description), stats(stats), equippedWeapon(nullptr), equippedShield(nullptr) {}

void Monster::equipItem(const Item& item) {
    switch (item.getType()) {
    case ItemType::Weapon:
        equippedWeapon = &item;  // Equip the weapon
        stats.setStrength(stats.getStrength() + item.getEffect());  // Increase strength
        break;
    case ItemType::Shield:
        equippedShield = &item;  // Equip the shield
        stats.setDefense(stats.getDefense() + item.getEffect());  // Increase defense
        break;
    default:
        std::cout << "This item cannot be equipped by the monster.\n";
        break;
    }
}

void Monster::attack(Player& target) {
    int damage = stats.getStrength() - target.getStats().getDefense();
    if (damage < 0) damage = 0;
    std::cout << name << " attacks " << target.getName() << " with " << (equippedWeapon ? equippedWeapon->getName() : "its claws")
        << " for " << damage << " damage!\n";
    target.takeDamage(damage);
}

void Monster::takeDamage(int damage) {
    stats.takeDamage(damage);
    if (stats.getHealth() <= 0) {
        std::cout << name << " is defeated!\n";
    }
}

std::string Monster::getName() const {
    return name;
}

std::string Monster::getDescription() const {
    return description;
}

bool Monster::alive() const {
    return stats.getHealth() > 0;
}
const Stats& Monster::getStats() const {
    return stats;
}


void Monster::defend() {

    // Similar logic to Player::defend()
    int defenseBoost = 10; // Adjust according to monster capabilities
    temporaryDefense += defenseBoost;
    std::cout << getName() << " is defending and increases defense by " << defenseBoost << "." << std::endl;

}

void Monster::resetDefense() {
    temporaryDefense = 0; // Reset any temporary defense boosts
    std::cout << getName() << " defense reset to normal." << std::endl;


}
