#pragma once
#ifndef __Human__
#define __Human__
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "Entity.h"
#include "Stats.h"

using namespace std;
class Room;

class Human : public Entity {
public:
	Human(const string& name, const string& description, shared_ptr<Room> room);
	~Human();

	virtual bool Go(const vector<string>& args);
	virtual void Look(const vector<string>& args) const;
	virtual bool Take(const vector<string>& args);
	virtual bool Drop(const vector<string>& args);
	virtual void Inventory() const;
	virtual bool Equip(const vector<string>& args);
	virtual bool UnEquip(const vector<string>& args);
	virtual bool AutoEquip();
	virtual bool Lock(const vector<string>& args);
	virtual bool UnLock(const vector<string>& args);
	virtual void Tick();

	virtual bool Attack(const vector<string>& args);

private:
	Stats stats;
};

#endif // __Human__

