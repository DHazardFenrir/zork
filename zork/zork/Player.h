#ifndef __Player__
#define __Player__

#include "Monster.h"
#include <memory>
#include "Stats.h"
#include "Item.h"
#include "Room.h"
#include "Human.h"
#include "Stats.h"
using namespace std;

class Player : public Human
{
public:
	Player(const std::string& name, const std::string& description, std::shared_ptr<Room> room, Stats stats);
	~Player();

	
	

public:
	Stats base_stats;
	Stats equipped_stats;
	vector<shared_ptr<Item>> equipped_items;
	vector<shared_ptr<Item>> inventory;

};

#endif //__Player__