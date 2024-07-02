#ifndef STATS_H
#define STATS_H

class Stats {
private:
    int health;
    int maxHealth;
    int strength;
    int defense;

public:
    Stats(int health, int strength, int defense);
    int getHealth() const;
    int getMaxHealth() const;
    void setHealth(int newHealth);
    int getStrength() const;
    void setStrength(int newStrength);
    int getDefense() const;
    void setDefense(int newDefense);
    void takeDamage(int amount);
};

#endif
