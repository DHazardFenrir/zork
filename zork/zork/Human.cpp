
#include "Entity.h"
#include "Human.h"
#include "Stats.h"
#include <memory>
#include <vector>
#include "globals.h"
#include "Stats.h"
#include "Monster.h"
#include "Room.h"
#include "NPC.h"
#include "Exit.h"
#include "Entity.h"
#include "Human.h"
using namespace std;
class Room;
class Exit;
Human::Human(const string& name, const string& description, shared_ptr<Room> room, int health, int strength, int defense, int speed) : Entity(name, description, room, EntityType::PLAYER), stats(health, strength, defense, speed) {
	
}

Human::~Human() = default;
void Human::Look(const vector<string>& args) const
{
	if (!CheckArgsSize(args, 2)) {
		if (Same(args[1], "me"))
		{
			std::cout << "\n" << name << "\n";
			cout << description << "\n";
			return;
		}
		for (const auto& child : parent->GetChildren()) {
			if (Same(child->GetName(), args[1])) {
				child->Look();
				return;
			 }

			if (child->GetType() == EntityType::EXIT) {
				auto exit = dynamic_pointer_cast<Exit>(child);
				if (exit && Same(args[1], exit->GetNameFrom(dynamic_pointer_cast<Room>(parent)))) {
					exit->Look();
					return;
				}
			}
		
		}
	    parent->Look();
	}
	else {
		cout << "\n" << name << "\n";
			cout << description << "\n";
	}
}



bool Human::Go(const std::string& direction) {
	auto currentRoom = std::dynamic_pointer_cast<Room>(this->location);
	if (args.size() != 2) {
		cout << "Usage: go <direction>" << endl;
		return false;
	}
	string direction = args[1];

	// Ensure 'location' is a shared_ptr<Room> member of Human.
	auto currentRoom = dynamic_pointer_cast<Room>(this->location);
	if (!currentRoom) {
		cout << "You are not in a room." << endl;
		return false;
	}

	auto exit = currentRoom->GetExit(direction);
	if (!exit) {
		cout << "There is no exit in that direction." << endl;
		return false;
	}

	this->location = exit->GetDestination(); // Assume Exit has GetDestination returning shared_ptr<Room>.
	cout << "You move " << direction << " to " << this->location->GetName() << "." << endl;
	return true;
}


// ----------------------------------------------------
bool Human::Take(const vector<string>& args)
{
	shared_ptr<Item> item = nullptr;

	if (CheckArgsSize(args, 4)) {
		// Look for the container item in the room
		for (const auto& child : GetParent()->GetChildren()) {
			if (Same(child->GetName(), args[3]) && child->GetType() == EntityType::ITEM) {
				item = dynamic_pointer_cast<Item>(child);
				break;
			}
		}

	

		if (!item) {
			cout << "\nCannot find '" << args[3] << "' in this room or in your inventory.\n";
			return false;
		}

		shared_ptr<Item> subitem = nullptr;
		for (const auto& subchild : item->GetChildren()) {
			if (Same(subchild->GetName(), args[1]) && subchild->GetType() == EntityType::ITEM) {
				subitem = dynamic_pointer_cast<Item>(subchild);
				break;
			}
		}

		if (!subitem) {
			cout << "\n" << item->GetName() << " does not contain '" << args[1] << "'.\n";
			return false;
		}

		cout << "\nYou take " << subitem->GetName() << " from " << item->GetName() << ".\n";
		item->RemoveChild(subitem);
		AddChild(subitem);
	}
	else if (args.size() == 2) {
		for (const auto& child : GetParent()->GetChildren()) {
			if (Same(child->GetName(), args[1]) && child->GetType() == EntityType::ITEM) {
				item = dynamic_pointer_cast<Item>(child);
				break;
			}
		}

		if (!item) {
			cout << "\nThere is no item here with that name.\n";
			return false;
		}

		cout << "\nYou take " << item->GetName() << ".\n";
		GetParent()->RemoveChild(item);
		AddChild(item);
	}

	return true;
}
shared_ptr<Room> Human::GetRoom() const {
	return dynamic_pointer_cast<Room>(parent);
}

bool Human::Drink(const vector<string>& args) {
	if (!CheckArgsSize(args, 2)) {
		cout << "\nInvalid command. Usage: drink <potion>\n";
		return false;
	}
	if (!IsAlive())
		return false;

	shared_ptr<Item> item = nullptr;
	for (const auto& inv_item : inventory) {
		if (Same(inv_item->GetName(), args[1]) && inv_item->GetItemType() == ItemType::POTION) {
			item = inv_item;
			break;
		}
	}

	if (!item) {
		cout << "\nYou don't have a potion with that name.\n";
		return false;
	}

	cout << "\nYou drink " << item->GetName() << ".\n";
	SetHealth(GetHealth() + item->GetStats().GetHealth());
	RemoveInventory(item);

	return true;
}
bool Human::Eat(const vector<string>& args) {
	if (!CheckArgsSize(args, 2)) {
		cout << "\nInvalid command. Usage: eat <food>\n";
		return false;
	}
	if (!IsAlive())
		return false;

	shared_ptr<Item> item = nullptr;
	for (const auto& inv_item : inventory) {
		if (Same(inv_item->GetName(), args[1]) && inv_item->GetItemType() == ItemType::FOOD) {
			item = inv_item;
			break;
		}
	}

	if (!item) {
		cout << "\nYou don't have food with that name.\n";
		return false;
	}

	cout << "\nYou eat " << item->GetName() << ".\n";
	SetHealth(GetHealth() + item->GetStats().GetHealth());
	RemoveInventory(item);

	return true;
}
// ----------------------------------------------------
void Human::Inventory() const
{
	

	if (inventory.empty()) {
		cout << GetName() << " does not own any items\n";
		return;
	}

	cout << "\n" << GetName() << " owns:\n";
	for (const auto& child : inventory) {
		if (auto item = dynamic_pointer_cast<Item>(child)) {
			if (item->GetItemType() == ItemType::WEAPON)
				cout << item->GetName() << " (as weapon)\n";
			else if (item->GetItemType() == ItemType::ARMOUR)
				cout << item->GetName() << " (as armour)\n";
			else if (item->GetItemType() == ItemType::POTION)
				cout << item->GetName() << " (as potion)\n";
			else if (item->GetItemType() == ItemType::FOOD)
				cout << item->GetName() << " (as food)\n";
			else
				cout << item->GetName() << "\n";
		}
	}
}

// ----------------------------------------------------
bool Human::Equip(const vector<string>& args)
{
	if (!CheckArgsSize(args, 2)) {
		cout << "\nInvalid command. Usage: equip <item>\n";
		return false;
	}
	if (!IsAlive())
		return false;

	shared_ptr<Item> item;
	for (const auto& child : inventory) {
		if (child->GetName() == args[1] && child->GetType() == EntityType::ITEM) {
			item = dynamic_pointer_cast<Item>(child);
			break;
		}
	}

	if (!item)
		return false;

	switch (item->GetItemType()) {
	case ItemType::WEAPON:
		myweapon = item;
		break;
	case ItemType::ARMOUR:
		myshield = item;
		break;
	default:
		return false;
	}

	cout << GetName() << " equips " << item->GetName() << "...\n";
	return true;
}

// ----------------------------------------------------
bool Human::UnEquip(const vector<string>& args)
{
	if (!CheckArgsSize(args, 2)) {
		cout << "\nInvalid command. Usage: Unquip <item>\n";
		return false;
	}
	if (!IsAlive())
		return false;

	shared_ptr<Item> item;
	for (const auto& child : GetChildren()) {
		if (child->GetName() == args[1] && child->GetType() == EntityType::ITEM) {
			item = dynamic_pointer_cast<Item>(child);
			break;
		}
	}

	if (!item)
		return false;

	if (item == myweapon)
		myweapon = nullptr;
	else if (item == myshield)
		myshield = nullptr;
	else
		return false;

	cout << GetName() << " un-equips " << item->GetName() << "...\n";
	return true;
}



// ----------------------------------------------------
bool Human::Lock(const vector<string>& args)
{
	if (!CheckArgsSize(args, 2)) {
		cout << "\nInvalid command. Usage lock <exit>\n";
		return false;
	}
	if (!IsAlive())
		return false;

	auto exit = dynamic_pointer_cast<Exit>(GetRoom()->GetExit(args[1]));

	if (!exit || exit->locked)
		return false;

	shared_ptr<Item> item;
	for (const auto& child : GetChildren()) {
		if (child->GetName() == args[3] && child->GetType() == EntityType::ITEM) {
			item = dynamic_pointer_cast<Item>(child);
			break;
		}
	}

	if (!item || exit->key != item)
		return false;

	cout << "\n" << GetName() << " locks " << exit->GetNameFrom(dynamic_pointer_cast<Room>(GetParent())) << "...\n";
	exit->locked = true;
	return true;
}

// ----------------------------------------------------
bool Human::UnLock(const vector<string>& args)
{
	if (!CheckArgsSize(args, 2)) {
		cout << "\nInvalid command. Usage: unlock <exito>\n";
		return false;
	}
	if (!IsAlive())
		return false;

	auto exit = dynamic_pointer_cast<Exit>(GetRoom()->GetExit(args[1]));

	if (!exit || !exit->locked)
		return false;

	shared_ptr<Item> item;
	for (const auto& child : GetChildren()) {
		if (child->GetName() == args[3] && child->GetType() == EntityType::ITEM) {
			item = dynamic_pointer_cast<Item>(child);
			break;
		}
	}

	if (!item || exit->key != item)
		return false;

	cout << "\n" << GetName() << " unlocks " << exit->GetNameFrom(dynamic_pointer_cast<Room>(GetParent())) << "...\n";
	exit->locked = false;
	return true;
}

bool Human::Talk(const vector<string>& args) {
	shared_ptr<NPC> npc = nullptr;

	for (const auto& child : GetParent()->GetChildren()) {
		if (Same(child->GetName(), args[1]) && child->GetType() == EntityType::NonPlayer) {
			npc = dynamic_pointer_cast<NPC>(child);
			break;
		}
	}

	if (npc) {
		cout << npc->GetDialogue() << "\n";
		return true;
	}

	cout << "No NPC found with that name.\n";
	return false;
}

// ----------------------------------------------------
bool Human::Drop(const vector<string>& args)
{
	if (!IsAlive())
		return false;

	shared_ptr<Item> item = nullptr;
	for (const auto& child : GetChildren()) {
		if (Same(child->GetName(), args[1]) && child->GetType() == EntityType::ITEM) {
			item = dynamic_pointer_cast<Item>(child);
			break;
		}
	}

	if (!item) {
		cout << "You don't have an item with that name.\n";
		return false;
	}

	cout << name << " drops " << item->GetName() << "...\n";
	GetParent()->AddChild(item);  // Move item to the current room
	RemoveChild(item);

	return true;
}


// ----------------------------------------------------
bool Human::IsAlive() const
{
	return stats.GetHealth() > 0;
}

// ----------------------------------------------------
void Human::Tick()
{
	if (combat_target)
	{
		bool target_found = false;
		auto children = parent->GetChildren();
		for (const auto& child : children)
		{
			if (child == combat_target)
			{
				target_found = true;
				break;
			}
		}

		if (target_found)
		{
			MakeAttack();
		}
		else
		{
			combat_target.reset(); // Use reset() to set the shared_ptr to nullptr
		}
	}
}
void Human::AddInventory(const vector<string>& args) {

	// Find the item in the room
	shared_ptr<Item> item = nullptr;
	for (const auto& child : GetRoom()->GetChildren()) {
		auto newitem= std::dynamic_pointer_cast<Item>(child);
		if (newitem && newitem->GetName() == args[1]) {
			item = newitem;
			break;
		}
	}
	if (!item) {
		cout << "Cannot add a null item to inventory.\n";
		return;
	}

	// Add the item to the inventory
	AddChild(item);

	// Equip the item automatically if it's a weapon or armor
	if (item->item_type == ItemType::WEAPON) {
		myweapon = item;
		cout << GetName() << " adds and equips " << item->GetName() << " as a weapon.\n";
	}
	else if (item->item_type == ItemType::ARMOUR) {
		myshield = item;
		cout << GetName() << " adds and equips " << item->GetName() << " as armor.\n";
	}
	else {
		cout << GetName() << " adds " << item->GetName() << " to the inventory.\n";
	}
}

void Human::RemoveInventory(shared_ptr<Item> item) {
	if (!item) {
		cout << "Cannot remove a null item from inventory.\n";
		return;
	}

	// Check if the item is in the inventory
	bool found = false;
	for (const auto& child : GetChildren()) {
		if (child->GetName() == item->GetName() && child->GetType() == EntityType::ITEM) {
			found = true;
			break;
		}
	}

	if (!found) {
		cout << GetName() << " does not have " << item->GetName() << " in the inventory.\n";
		return;
	}

	// If the item is equipped, unequip it first
	if (item == myweapon) {
		myweapon = nullptr;
		cout << GetName() << " unequips " << item->GetName() << ".\n";
	}
	else if (item == myshield) {
		myshield = nullptr;
		cout << GetName() << " unequips " << item->GetName() << ".\n";
	}

	// Remove the item from the inventory
	RemoveChild(item);
	cout << GetName() << " removes " << item->GetName() << " from the inventory.\n";

	// Add the item to the parent room
	GetParent()->AddChild(item);
}
// ----------------------------------------------------
bool Human::Attack(const vector<string>& args)
{
	if (args.size() < 2) {
		std::cerr << "Invalid attack command. Please specify a target.\n";
		return false;
	}

	// Find the monster in the room
	bool targetfound = false;
	shared_ptr<Monster> target = nullptr;
	for (const auto& child : GetRoom()->GetChildren()) {
		auto monster = std::dynamic_pointer_cast<Monster>(child);
		if (monster && monster->GetName() == args[1]) {
			targetfound = true;
			target = monster;
			break;
		}
	}

	if (!targetfound) {
		std::cerr << "No such monster found.\n";
		return false;
	}

	combat_target = target;
	std::cout << "\n" << name << " attacks " << target->GetName() << "!\n";
	MakeAttack();
	return true;
}

// ----------------------------------------------------
int Human::MakeAttack()
{

	if (!IsAlive() || combat_target != NULL || !combat_target->IsAlive()) {
		combat_target = nullptr;
		return 0;
	}

	int attackDamage = GetStrength();
	if (myweapon) {
		attackDamage += myweapon->GetValue();
	}
	int damageDealt = combat_target->ReceiveAttack(attackDamage);

	
	cout << name << " attacks " << combat_target->GetName() << " for " << damageDealt << " damage \n";
	
	// Update combat target if it has died
	if (!combat_target->IsAlive()) {
		combat_target = nullptr;  // Clear target if it's dead
	}
	return damageDealt;
}

// ----------------------------------------------------
int Human::ReceiveAttack(int damage)
{
	// Calculate the total defense from the Human's stats and equipped shield (armor)
	int totalDefense = GetDefense();
	if (myshield) {
		totalDefense += myshield->GetValue(); // Assuming GetValue returns the defense value for a shield
	}

	// Calculate the actual damage considering the total defense
	int actualDamage = max(0, damage - totalDefense);

	// Reduce the health by the actual damage
	SetHealth(GetHealth() - actualDamage);

	// Output the result (assuming a player is in the room)
	cout << name << " is hit for " << actualDamage << " damage (" << totalDefense << " defense).\n";

	return actualDamage;
	
}

// ----------------------------------------------------
void Human::Die()
{
	if (!Human::IsAlive())
		cout << name << " dies.\n";
}

// ----------------------------------------------------
bool Human::Loot(const vector<string>& args)
{
	shared_ptr<Entity> target = nullptr;

	for (const auto& child : parent->GetChildren()) {
		if ((child->GetType() == EntityType::MONSTER && Same(child->GetName(), args[1])) ||
			(child->GetType() == EntityType::NonPlayer && Same(child->GetName(), args[1]))) {
			target = child;
			break;
		}
	}

	if (target == nullptr) {
		cout << "\n" << args[1] << " is not here.\n";
		return false;
	}

	// Check if the target is dead. This assumes that Monster and NPC have the IsAlive() method.
	bool isAlive = false;
	if (target->GetType() == EntityType::MONSTER) {
		auto monster = dynamic_pointer_cast<Monster>(target);
		if (monster) {
			isAlive = monster->IsAlive();
		}
	}
	else if (target->GetType() == EntityType::NonPlayer) {
		auto npc = dynamic_pointer_cast<NPC>(target);
		if (npc) {
			isAlive = npc->IsAlive();
		}
	}

	if (isAlive) {
		cout << "\n" << target->GetName() << " cannot be looted until it is killed.\n";
		return false;
	}

	vector<shared_ptr<Entity>> items;
	for (const auto& child : target->GetChildren()) {
		if (child->GetType() == EntityType::ITEM) {
			items.push_back(child);
		}
	}

	if (!items.empty()) {
		cout << "\nYou loot " << target->GetName() << "'s corpse:\n";
		for (const auto& item : items) {
			cout << "You find: " << item->GetName() << "\n";
			target->RemoveChild(item);  // Remove from the target
			AddChild(item);             // Add to the current human
		}
	}
	else {
		cout << "\nYou loot " << target->GetName() << "'s corpse, but find nothing there.\n";
	}

	return true;
}
// Getters
int Human::GetHealth() const { return stats.GetHealth(); }
int Human::GetStrength() const { return stats.GetStrength(); }
int Human::GetDefense() const { return stats.GetDefense(); }
int Human::GetSpeed() const { return stats.GetSpeed(); }

// Setters
void Human::SetHealth(int value) { stats.SetHealth(value); }
void Human::SetStrength(int value) { stats.SetStrength(value); }
void Human::SetDefense(int value) { stats.SetDefense(value); }
void Human::SetSpeed(int value) { stats.SetSpeed(value); }
