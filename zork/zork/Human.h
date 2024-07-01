#pragma once
#ifndef __Human_H__
#define __Human_H__
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "Entity.h"
#include "Stats.h"
#include "Item.h"

using namespace std;
class Room;
class Monster;
class Human : public Entity {
public:
	Human(const string& name, const string& description, shared_ptr<Room> room, int health = 100, int strength = 10, int defense = 5, int speed = 5);
	~Human();

	virtual bool Go(const vector<string>& args);
	virtual void Look(const vector<string>& args) const;
	virtual bool Take(const vector<string>& args);
	virtual bool Drop(const vector<string>& args);
	virtual void Inventory() const;
	virtual bool Equip(const vector<string>& args);
	virtual bool UnEquip(const vector<string>& args);
	virtual bool Lock(const vector<string>& args);
	virtual bool UnLock(const vector<string>& args);
	virtual void Tick();
	virtual bool Loot(const vector<string>& args);
	virtual bool Talk(const vector<string>& args);
	virtual bool Drink(const vector<string>& args);
	virtual bool Eat(const vector<string>& args);
	virtual int MakeAttack();
	virtual void Die();
	virtual int ReceiveAttack(int damage);
	virtual bool Attack(const vector<string>& args);
	virtual bool IsAlive() const;
    virtual shared_ptr<Room> GetRoom() const; 
	virtual void AddInventory(const vector<string>& args);
	virtual void RemoveInventory(shared_ptr<Item> item);
	//Getters for stats
	int GetHealth() const;
	int GetStrength() const;
	int GetDefense() const;
	int GetSpeed() const;

	void SetHealth(int value);
	void SetStrength(int value);
	void SetDefense(int value);
	void SetSpeed(int value);

private:
	Stats stats;
	vector<shared_ptr<Item>> inventory;
	shared_ptr<Item> myweapon;
	shared_ptr<Item> myshield;
	shared_ptr<Monster> combat_target;
};

#endif // __Human_H__

