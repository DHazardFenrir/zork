#include "Item.h"

Item::Item(std::string name, std::string description, ItemType type, int effect)
    : name(name), description(description), type(type), effect(effect) {}

std::string Item::getName() const {
    return name;
}

std::string Item::getDescription() const {
    return description;
}

ItemType Item::getType() const {
    return type;
}

int Item::getEffect() const {
    return effect;
}
