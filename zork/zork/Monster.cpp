#include <iostream>
#include "Monster.h"
#include "Room.h"
#include "Item.h"

#include <memory>
using namespace std;
Monster::Monster(const std::string& name, const std::string& description, std::shared_ptr<Room> room, int health, int strength, int defense, int speed, std::shared_ptr<Item> weapon)
	: Entity(name, description, room, EntityType::MONSTER), stats(health, strength, defense, speed), weapon(weapon) {
	if (!this->weapon) {
		AutoEquip();
	}
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

void Monster::SetDefense(int value) {
	stats.SetDefense(value);
}

void Monster::SetStrength(int value) {
	stats.SetStrength(value);
}

void Monster::SetSpeed(int value) {
	stats.SetSpeed(value);
}


EntityType Monster::GetType() const {
	return EntityType::MONSTER;
}

shared_ptr<Room> Monster::GetRoom() const {
	return dynamic_pointer_cast<Room>(parent);
}

bool Monster::PlayerInRoom() const {
	for (const auto& child : children) {
		if (child->GetType() == EntityType::PLAYER) {
			return true;
		}
		return false;
	}
}

int Monster::MakeAttack()
{
	if (!IsAlive()) {
		combat_target.reset();  // Reset the weak_ptr if the target is not alive
		return 0;
	}

	auto target = combat_target.lock();  // Convert weak_ptr to shared_ptr
	if (!target || !target->IsAlive()) {
		combat_target.reset();  // Clear target if it's dead
		return 0;
	}

	int attackDamage = GetStrength();
	if (weapon) {
		attackDamage += weapon->GetValue();
	}
	int damageDealt = target->ReceiveAttack(attackDamage);

	if (PlayerInRoom()) {
		std::cout << GetName() << " attacks " << target->GetName() << " for " << damageDealt << " damage \n";
	}

	if (!target->IsAlive()) {
		combat_target.reset();  // Clear target if it's dead
	}

	return damageDealt;
}

int Monster::ReceiveAttack(int damage) {
	int defense = GetDefense();
	if (armor) {
		defense += armor->GetValue();
	}
	int actualDamage = max(0, damage - defense);

	SetHealth(GetHealth() - actualDamage);

	if (PlayerInRoom()) {
		cout << name << "is hit for " << actualDamage << "damage (" << defense << " defense.\n";
	}

	

	if (!IsAlive()) {
		Die();
	}
	return actualDamage;
}

void Monster::Die() {
	if (PlayerInRoom()) {
		cout << name << "dies ";
	}
}


bool Monster::AutoEquip() {
	if (weapon) {
		// Ya se ha proporcionado un arma, no necesitamos buscar más
		return true;
	}

	for (const auto& item : GetChildren()) {
		auto i = std::dynamic_pointer_cast<Item>(item);
		if (i->GetItemType() == ItemType::WEAPON) {
			weapon = i;
		}
		else if (i->GetItemType() == ItemType::ARMOUR) {
			armor = i;
		}
	}
	return true;
	
}