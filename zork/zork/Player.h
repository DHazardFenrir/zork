#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Stats.h"
#include "Item.h"
#include "Room.h"
#include "Status.h"

class Player {
private:
    std::string name;
    Stats stats;
    std::vector<Item> inventory;
    const Item* equippedWeapon = nullptr;
    const Item* equippedShield = nullptr;
    int temporaryDefense;
    Status currentStatus;

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
    void defend();
    void resetDefense();
    void addItem(const Item& item);
    bool removeItem(const std::string& itemName);
    void useItem();
    void showInventory() const;
    void pickUpItem(Room& room);
    Item* findItemInInventory(const std::string& itemName);
    bool unlockExit(Room& room, const std::string& direction);
    void inflictStatus(Status status);
    void applyStatusEffects();
    void cureStatus(Status status);
    void useSpecificItem(const Item& item); 
    Status getStatus() const; 
    void setStatus(Status status); 
};

#endif
