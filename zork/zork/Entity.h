
#ifndef __Entity__
#define __Entity__
#include <string>
#include <vector>
#include <memory> // Para el uso de std::shared_ptr

#include <iostream>
using namespace std;

enum class EntityType {
	ENTITY,
	ROOM,
	EXIT,
	ITEM,
	MONSTER,
	HUMAN
};
class Entity {
public:
	Entity(const string& name, const string& description, shared_ptr<Entity> parent = nullptr);
	virtual ~Entity();

	virtual void Look() const;
	virtual EntityType GetType() const;
	void AddChild(std::shared_ptr<Entity> child);
	void RemoveChild(std::shared_ptr<Entity> child);

	string GetName() const;
	string GetDescription() const;
	shared_ptr<Entity> GetParent() const;
	const vector<shared_ptr<Entity>>& GetChildren() const;


protected:
	std::string name;
	std::string description;
	std::shared_ptr<Entity> parent;
	std::vector<std::shared_ptr<Entity>> children; // Lista de hijos
};

#endif // __Entity__

