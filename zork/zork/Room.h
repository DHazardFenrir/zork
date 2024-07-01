#ifndef __ROOM__
#define __ROOM__

#include <string>
#include <vector>
#include <memory>
#include "Entity.h"

class Exit;
class Item;

using namespace std;

class Room : public Entity {
public:
    Room(const string& name, const string& description) :
        Entity(name, description, nullptr, EntityType::ROOM)  // Pass appropriate parameters
    {
    }
    ~Room();

    void Look() const override;
    void AddItem(shared_ptr<Item> item);
    void AddEntity(shared_ptr<Entity> entity);
    EntityType GetType() const override;
    shared_ptr<Exit> GetExit(const string& direction) const;  // Return a shared_ptr<Exit>

    const vector<shared_ptr<Entity>>& GetEntities() const { return entities; }
    const vector<shared_ptr<Item>>& GetItems() const { return items; }

private:
    vector<shared_ptr<Item>> items;
    vector<shared_ptr<Entity>> entities;
};

#endif // __ROOM__
