
#ifndef __ENTITY__
#define __ENTITY__

#include <vector>
#include <memory> // Para el uso de std::shared_ptr
class Room;
#include <iostream>
using namespace std;

enum EntityType {
	ENTITY,
	ROOM,
	EXIT,
	ITEM,
	MONSTER,
	PLAYER,
	NonPlayer
};
class Entity: public enable_shared_from_this <Entity>{
	friend class std::shared_ptr<Entity>;

public:
	Entity(const std::string& name, const std::string& description, shared_ptr<Entity> parent, enum EntityType type);
	virtual ~Entity();

	virtual void Look() const;
	virtual enum EntityType GetType() const;
	void AddChild(std::shared_ptr<Entity> child);
	void RemoveChild(std::shared_ptr<Entity> child);

	std::string GetName() const;
	std::string GetDescription() const;
	shared_ptr<Entity> GetParent() const;
	virtual void Tick();
	const vector<shared_ptr<Entity>>& GetChildren() const;


protected:
	std::string name;
	std::string description;
	std::shared_ptr<Entity> parent;
	std::vector<std::shared_ptr<Entity>> children; 
	enum EntityType type;// Lista de hijos
};

#endif // __ENTITY__

