
#ifndef __Item_H__
#define __Item_H__
#include <string>
#include "Entity.h"
#include <Stats.h>
class Room;

using namespace std;

enum ItemType
{

	WEAPON,
	ARMOUR,
	POTION,
	FOOD
};

class Item : public Entity
{
	Item(const string& name, const string& description, shared_ptr<Room> room, ItemType item_type = POTION);
	~Item();

	void Look() const override;
	int GetValue() const;

public:
	Stats stats;
	ItemType item_type;
};

#endif //__Item_H__