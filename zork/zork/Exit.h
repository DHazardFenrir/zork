#include <iostream>
#include "Exit.h"
#include "Room.h"

using namespace std;

Exit::Exit(const string& name, const string& opposite_name, const string& description, shared_ptr<Room> origin, shared_ptr<Room> destination, bool one_way) :
    Entity(name, description, origin, EntityType::EXIT),
    closed(false), locked(false), key(nullptr), one_way(one_way), destination(destination), opposite_name(opposite_name)
{
    // Corrected: Removed unsafe use of 'this' in shared_ptr
    // Instead, manage the bidirectional relationship outside of the constructor
}

Exit::~Exit()
{
    // Destructor body can be left empty or defaulted if no manual resource management is needed
}

void Exit::Look() const
{
    cout << name << " to " << opposite_name << "\n";
    cout << description << "\n";
}

const string& Exit::GetNameFrom(const shared_ptr<Room>& room) const
{
    if (room == parent)
        return name;
    if (room == destination)
        return opposite_name;

    return name;  // Default case
}

shared_ptr<Room> Exit::GetDestinationFrom(const shared_ptr<Room>& room) const
{
    if (room == parent) {
        return destination;
    }
    if (room == destination) {
        return std::dynamic_pointer_cast<Room>(parent);  // Safe conversion from Entity to Room
    }

    return nullptr;  // Return nullptr if the room does not match
}

EntityType Exit::GetType() const {
    return EntityType::EXIT;
}
