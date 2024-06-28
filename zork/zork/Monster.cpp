#include <iostream>
#include "Monster.h"
#include "Room.h"
#include "Item.h"

#include <memory>
using namespace std;
Monster::Monster(const string& name, const string& description, shared_ptr<Room> room, int health, int strength, int defense, int speed) : Entity(name, description, room), stats(health, strength, defense, speed) {

}

Monster::~Monster() {}

void Monster::Look(const vector<string>& args) const
{
	if (IsAlive())
	{
		cout << name << "\n";
		cout << description << "\n";
	}
	else
	{
		cout << name << "'s corpse\n";
		cout << "Here lies dead: " << description << "\n";
	}
}

bool Monster::IsAlive() const
{
	return stats.GetHealth() > 0;
}

int Monster::GetHealth() const {
	return stats.GetHealth();
}

int Monster::GetStrength() const {
	return stats.GetStrength();
}

int Monster::GetDefense() const {
	return stats.GetDefense();
}

int Monster::GetSpeed() const {
	return stats.GetSpeed();
}

void Monster::SetHealth(int value) {
	stats.SetHealth(value);
}

EntityType Monster::GetType() const {
	return EntityType::MONSTER;
}

shared_ptr<Room> Monster::GetRoom() const {
	return dynamic_cast<shared_ptr<Room>>(parent);
}

bool Monster::PlayerInRoom() const {
	for (const auto& child : children) {
		if (child->GetType() == EntityType::PLAYER) {
			return true;
		}
		return false;
	}
}