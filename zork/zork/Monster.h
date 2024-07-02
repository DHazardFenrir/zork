#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include "Stats.h"
#include "Item.h"  // Ensure the Item class is included
class Player;
class Monster {
private:
    std::string name;
    std::string description;
    Stats stats;
    const Item* equippedWeapon;
    const Item* equippedShield;

public:
    Monster(std::string name, std::string description, Stats stats);
    void attack(Player& target);
    void takeDamage(int damage);
    std::string getName() const;
    std::string getDescription() const;
    bool alive() const;
    void equipItem(const Item& item);
    const Stats& getStats() const;
    void defend();
    void resetDefense();
    int temporaryDefense;
};

#endif
