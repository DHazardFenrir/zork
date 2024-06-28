#ifndef __Room__
#define __Room__

#include <string>

#include "Entity.h"


class Exit;
class Item;

using namespace std;

class Room : public Entity
{
public:
	Room(const string& name, const string& description);
	~Room();

	void Look() const override;
	void AddItem(shared_ptr<Item> item);
	void AddEntity(shared_ptr<Entity> entity);
	EntityType GetType() const override;
	shared_ptr<Exit> GetExit(const string& direction) const;

private:
	vector<shared_ptr<Item>> items;
	vector<shared_ptr<Entity>> entities;
};

#endif //__Room__