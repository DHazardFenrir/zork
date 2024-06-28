#ifndef __Exit__
#define __Exit__

#include <string>
#include "Entity.h"

class Room;

using namespace std;

class Exit : public Entity
{
public:
	Exit(const string& name, const string& opposite_name, const string& description, shared_ptr<Room> origin, shared_ptr<Room> destination, bool one_way = false);
	~Exit();

	void Look() const;
	EntityType GetType() const override;
	const string& GetNameFrom(const Room* room) const;
	shared_ptr<Room> GetDestinationFrom(const Room* room) const;

public:
	bool one_way;
	bool closed;
	bool locked;
	string opposite_name;
	shared_ptr<Room> destination;
	shared_ptr<Entity> key;
};

#endif //__Exit__