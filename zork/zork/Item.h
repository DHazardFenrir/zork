#ifndef ITEM_H
#define ITEM_H

#include <string>

enum class ItemType { Weapon, Shield, Potion, Food };

class Item {
private:
    std::string name;
    std::string description;
    ItemType type;
    int effect;  // Can be positive or negative based on the item type

public:
    Item(std::string name, std::string description, ItemType type, int effect);
    std::string getName() const;
    std::string getDescription() const;
    ItemType getType() const;
    int getEffect() const;
};

#endif
