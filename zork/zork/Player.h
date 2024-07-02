#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Item.h"
#include "Stats.h"
#include "Room.h"  // Include Room header

class Player {
private:
    std::string name;
    Stats stats;
    std::vector<Item> inventory;
    const Item* equippedWeapon = nullptr;
    const Item* equippedShield = nullptr;
    int temporaryDefense = 0;

public:
    Player(std::string name, Stats stats);
    void attack(Monster& target);
    void lookAtItem(Room& room, const std::string& itemName);
    void takeDamage(int damage);
    std::string getName() const;
    bool isAlive() const;
    const Stats& getStats() const;
    void equipItem(const Item& item);
    void useItem(const Item& item);
    void useItem();
    void defend();
    void resetDefense();
    void addItem(const Item& item);
    bool removeItem(const std::string& itemName);
    void showInventory() const;
    void pickUpItem(Room& room);
    Item* findItemInInventory(const std::string& itemName);
};

#endif // PLAYER_H
