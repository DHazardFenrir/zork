#ifndef __Monster__
#define __Monster__

#include <string>
#include "Entity.h"
#include "Player.h"
#include "Stats.h"
#include <memory>
#include <vector>
class Room;
class Item;
class Player;
using namespace std;

class Monster : public Entity
{
public:
	Monster(const string& name, const string& description, shared_ptr<Room> room, int health = 100, int strength = 10, int defense = 5, int speed = 5, shared_ptr<Item> weapon = nullptr);
	~Monster();
	virtual EntityType GetType() const override;
	virtual void Look(const vector<string>& args) const;
	virtual bool AutoEquip();
	virtual void Tick();
	int GetHealth() const;
	int GetStrength() const;
	int GetDefense() const;
	int GetSpeed() const;
	void SetCombatTarget(std::shared_ptr<Player> target) { combat_target = target; }
	std::weak_ptr<Player> GetCombatTarget() const { return combat_target; }
	void SetHealth(int value);
	void SetStrength(int value);
	void SetDefense(int value);
	void SetSpeed(int value);
	
	virtual int MakeAttack();
	virtual int ReceiveAttack(int damage);
	virtual void Die();
	


	shared_ptr<Room> GetRoom() const;
	bool PlayerInRoom() const;
	bool IsAlive() const;


private:
	Stats stats;
	std::weak_ptr<Player> combat_target;;
	shared_ptr<Item> weapon;
	shared_ptr<Item> armor;
};

#endif //__Monster__