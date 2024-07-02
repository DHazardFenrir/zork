#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Stats.h"
#include "Monster.h"
#include "Item.h"

class Player {
private:
    std::string name;
    Stats stats;
    std::vector<Item> inventory;
    const Item* equippedWeapon;
    const Item* equippedShield;

public:
    Player(std::string name, Stats stats);
    void attack(Monster& target);
    void takeDamage(int damage);
    std::string getName() const;
    bool isAlive() const;
    void equipItem(const Item& item);
    void useItem(const Item& item);
    const Stats& getStats() const;
};

#endif
