#include "Stats.h"

Stats::Stats(int health, int strength, int defense, int speed) : health(health),strength(strength), defense(defense),speed(speed) {

}

int Stats::GetHealth() const {
	return health;
}

void Stats::SetHealth(int value) {
	health = value;
}

int Stats::GetStrength() const {
	return strength;
}

void Stats::SetStrength(int value){
	strength = value;
}
int Stats::GetDefense() const {
	return defense;
}

void Stats::SetDefense(int value) {
	defense = value;
}

int Stats::GetSpeed() const {
	return speed;
}

void SetSpeed(int value) {
	speed = value;
}