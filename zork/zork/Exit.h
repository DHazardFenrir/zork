#ifndef __EXIT__
#define __EXIT__

#include <string>
#include "Entity.h"

class Item;
class Room;

using namespace std;

class Exit : public Entity {
public:
    Exit(const string& name, const string& opposite_name, const string& description, shared_ptr<Room> origin, shared_ptr<Room> destination, bool one_way = false);
    ~Exit();

    void Look() const override;
    EntityType GetType() const override;
    const string& GetNameFrom(const shared_ptr<Room>& room) const;  // Accept shared_ptr<Room>
    shared_ptr<Room> GetDestinationFrom(const shared_ptr<Room>& room) const;  // Accept shared_ptr<Room>

public:
    bool one_way;
    bool closed;
    bool locked;
    string opposite_name;
    shared_ptr<Room> destination;
    shared_ptr<Item> key;
};

#endif // __EXIT__
