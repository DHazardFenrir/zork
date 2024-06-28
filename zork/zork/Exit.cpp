#include "Exit.h"
#include <iostream>
#include "Room.h"


// ----------------------------------------------------
Exit::Exit(const string& name, const string& opposite_name, const string& description, shared_ptr<Room> origin, shared_ptr<Room> destination, bool one_way) :
	Entity(name, description, origin),
	closed(false), locked(false), key(nullptr), one_way(one_way), destination(destination), opposite_name(opposite_name)
{
	

	if (!one_way)
		destination->AddEntity(shared_from_this());
}

// ----------------------------------------------------
Exit::~Exit()
{
}


// ----------------------------------------------------
void Exit::Look() const
{
	cout << name << " to " << opposite_name << "\n";
	cout << description << "\n";
}

// ----------------------------------------------------
const string& Exit::GetNameFrom(const shared_ptr<Room> room) const
{
	if (room == parent)
		return name;
	if (room == destination)
		return opposite_name;

	static const string error_name = "unknown";
	return error_name; 
}

// ----------------------------------------------------
shared_ptr<Room> Exit::GetDestinationFrom(const shared_ptr<Room> room) const
{
	if (room == parent)
		return destination;
	if (room == destination)
		return shared_ptr<Room>(parent);

	return nullptr;
}

EntityType Exit::GetType() const {
	return EntityType::EXIT
}