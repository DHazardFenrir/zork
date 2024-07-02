#include "Stats.h"

Stats::Stats(int health, int strength, int defense)
    : health(health), strength(strength), defense(defense) {
    maxHealth = health;
}

int Stats::getHealth() const {
    return health;
}
int Stats::getMaxHealth() const {
    
    return maxHealth;
}

void Stats::setHealth(int newHealth) {
    health = newHealth;
}

int Stats::getStrength() const {
    return strength;
}

void Stats::setStrength(int newStrength) {
    strength = newStrength;
}

int Stats::getDefense() const {
    return defense;
}

void Stats::setDefense(int newDefense) {
    defense = newDefense;
}

void Stats::takeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}

