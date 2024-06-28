
#ifndef __Item__
#define __Item__
#include <iostream>
#include "Room.h"
#include "Exit.h"
#include "globals.h"
#include "Item.h"
#include "Stats.h"

// ----------------------------------------------------
Item::Item(const string& name, const string& description, shared_ptr<Room> room, ItemType item_type) :
	Entity(name, description, room), item_type(item_type), stats()
{
	if (item_type == WEAPON) {
		stats.SetStrength(1);
		stats.SetDefense(2);
	}
	else if (item_type == ARMOUR) {
		stats.SetDefense(5);
		stats.SetSpeed(1);
	}
	else if (item_type == POTION) {
		stats.SetHealth(20);
	}
	else if (item_type == FOOD) {
		stats.SetHealth(3);
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

// ----------------------------------------------------
int Item::GetValue() const
{
	return Roll(min_value, max_value);
}
#endif