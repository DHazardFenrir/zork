#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <map>
#include <vector>
#include "Item.h"
#include "Monster.h"

class Room {
private:
    std::string description;
    std::map<std::string, Room*> exits;
    std::vector<Item> items;
    Monster* monster;
    std::map<std::string, bool> lockedExits;
    std::map<std::string, int> lockIds; // Which key is needed to open the lock

public:
    Room(std::string desc);
    void connect(Room* room, const std::string& direction);
    void addItem(const Item& item);
    void setMonster(Monster* m);
    bool hasMonster() const;  // Check if the room has a monster
    Monster* getMonster() const;  // Get the monster in the room
    std::string getDescription() const;  // Get the description of the room
    const std::map<std::string, Room*>& getExits() const;  // Get exits from the room
    void describe() const;
    Room* move(const std::string& direction);
    void removeItem(const std::string& itemName);
    void showItems() const;
    std::vector<Item>& getItems(); // Getter for items
    std::vector<std::string> getItemNames() const;
    Item* getItem(const std::string& itemName); // Method to get an item by name
    void setLockedExit(const std::string& direction, int lockId);
    bool unlockExit(const std::string& direction, const Item& key);
    bool isExitLocked(const std::string& direction) const;  // Check if an exit is locked
};

#endif
