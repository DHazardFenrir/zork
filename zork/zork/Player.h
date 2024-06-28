#ifndef __Player__
#define __Player__

#include "Monster.h"
#include <memory>
#include "Stats.h"
using namespace std;

class Player : public Monster
{
public:
	Player(const string& name, const string& description, shared_ptr<Room>room);
	~Player();

	bool Go(const vector<string>& args) override;
	void Look(const vector<string>& args) const override;
	bool Take(const vector<string>& args) override;
	bool Drop(const vector<string>& args) override;
	void Inventory() const override;
	void Drink(const vector<string>& args) override;
	void Eat(const vector<string>& args) override;
	bool Equip(const vector<string>& args) override;
	bool UnEquip(const vector<string>& args) override;
	bool Examine(const vector<string>& args) const override;
	bool Attack(const vector<string>& args) override;
	bool Loot(const vector<string>& args) override;
	bool Lock(const vector<string>& args) override;
	bool UnLock(const vector<string>& args) override;

public:
	Stats base_stats;
	Stats equipped_stats;
	vector<shared_ptr<Item>> equipped_items;
	vector<shared_ptr<Item>> inventory;
};

#endif //__Player__