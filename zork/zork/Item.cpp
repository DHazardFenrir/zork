
#ifndef __Item__
#define __Item__
#include <iostream>
#include "Room.h"
#include "Exit.h"
#include "globals.h"
#include "Item.h"
#include "Stats.h"

Item::Item(const string& name, const string& description, shared_ptr<Room> room, ItemType item_type, const Stats& stats)
	: Entity(name, description, room, EntityType::ITEM), item_type(item_type), stats(stats) // Create a copy of stats
{
	if (item_type == ItemType::WEAPON) {
		cout << "Strength: " << stats.GetStrength() << "\n";
		cout << "Defense: " << stats.GetDefense() << "\n";
	}
	else if (item_type == ItemType::ARMOUR) {
		cout << "Defense: " << stats.GetDefense() << "\n";
		cout << "Speed: " << stats.GetSpeed() << "\n";
	}
	else if (item_type == ItemType::POTION) {
		cout << "Health: " << stats.GetHealth() << "\n";
	}
	else if (item_type == ItemType::FOOD) {
		cout << "Health: " << stats.GetHealth() << "\n";
	}

}

// ----------------------------------------------------
Item::~Item()
{}

// ----------------------------------------------------
void Item::Look() const
{
	cout << "\n" << name << "\n";
	cout << description << "\n";

	if (item_type == WEAPON)
	{
		cout << "Strength: " << stats.GetStrength() << "\n";
		cout << "Defense: " << stats.GetDefense() << "\n";
	}
	else if (item_type == ARMOUR)
	{
		cout << "Defense: " << stats.GetDefense() << "\n";
		cout << "Speed: " << stats.GetSpeed() << "\n";
	}
	else if (item_type == POTION)
	{
		cout << "Health: " << stats.GetHealth() << "\n";
	}
	
	
}

ItemType Item::GetItemType() const {
	return item_type;
}

void Item::SetStats(const Stats& new_stats) {
	stats = new_stats;
}
// ----------------------------------------------------
int Item::GetValue() const
{
	switch (item_type) {
	case ItemType::WEAPON:
		return stats.GetStrength(), stats.GetDefense(); // Suma de los atributos relevantes para el arma
	case ItemType::ARMOUR:
		return stats.GetDefense(), stats.GetSpeed(); // Suma de los atributos relevantes para la armadura
	case ItemType::POTION:
	case ItemType::FOOD:
		return stats.GetHealth(); // Retorna la salud para pociones y comida
	default:
		return 0;
	}
}

Stats Item::GetStats() const {
	return stats;
}
#endif