#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>

enum class ItemType { Weapon, Shield, Food, Potion, Key, Container };

class Item {
private:
    std::string name;
    std::string description;
    ItemType type;
    int effect;
    std::vector<Item> contents;  // Container for nested items

public:
    Item(std::string name, std::string description, ItemType type, int effect);
    std::string getName() const;
    std::string getDescription() const;
    ItemType getType() const;
    int getEffect() const;
    const std::vector<Item>& getContents() const;  // Accessor for nested items (const)
    std::vector<Item>& getMutableContents();  // Accessor for nested items (non-const)
    void addItem(const Item& item);  // Method to add nested items
};

#endif
