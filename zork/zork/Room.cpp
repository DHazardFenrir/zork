#include <iostream>
#include "globals.h"
#include "Exit.h"
#include "Item.h"
#include "Monster.h"
#include "Room.h"

// ----------------------------------------------------
Room::Room(const string& name, const string& description) :
	Entity(name, description, nullptr)
{
	
}

// ----------------------------------------------------
Room::~Room()
{
}

void Room::AddItem(shared_ptr<Item> item) {
	items.push_back(item);
}

void Room::AddEntity(shared_ptr<Entity> entity) {
	entities.push_back(entity);
}
// ----------------------------------------------------
void Room::Look() const
{
	cout << "\n" << name << "\n";
	cout << description;

	for (const auto& entity : entities) {
		if (entity->GetType == EntityType::EXIT); {
			shared_ptr<Exit> ex = dynamic_pointer_cast<Exit>(entity);
			if (ex) {
				cout << "\nDirection (" << ex->GetNameFrom(this) << ") you see " << ex->GetDestinationFrom(this)->GetName();
			}
		}
		
	}

	for (const auto& item : items) {
		cout << "\nThere is an item here: " << item->GetName();
	}

	for (const auto& entity : entities) {
		if (entity->GetType() == EntityType::MONSTER) {
			shared_ptr<Monster> monster = dynamic_pointer_cast<Monster>(entity);
			if (monster) {
				cout << "\nThere is someone else here: " << monster->GetName();
				if (!monster->IsAlive()) {
					cout << " (dead)";
				}
			}
		}
	}

	cout << "\n";
}

// ----------------------------------------------------
shared_ptr<Exit> Room::GetExit(const string& direction) const
{
	for (const auto& entity : entities) {
		if(entity->GetType() == EntityType::EXIT) {
			shared_ptr<Exit> exit = dynamic_pointer_cast<Exit>(entity);

			if (exit && exit->GetNameFrom(this) == direction) {
				return exit;
			}
		}
	}
	return nullptr;
	
}

EntityType Room::GetType() const {
	return EntityType::ROOM;
}


