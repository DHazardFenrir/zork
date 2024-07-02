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
};

#endif
