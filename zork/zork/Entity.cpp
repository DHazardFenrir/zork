
#include <string>
#include "Room.h"
#include "Entity.h"

using namespace std;
Entity::Entity(const std::string& entituName, const std::string& description, shared_ptr<Entity> parent, enum EntityType type) {
    this->name = entituName; // Use 'this' pointer to avoid ambiguity with local variable
    this->description = description;
    this->parent = parent;
    this->type = type;
}

Entity::~Entity() {}
void Entity::Tick()
{}

void Entity::Look() const {
    std::cout << name << ": " << description << std::endl;
}

void Entity::AddChild(shared_ptr<Entity> child) {
    children.push_back(child);
}

void Entity::RemoveChild(shared_ptr<Entity> child) {
    auto it = std::remove(children.begin(), children.end(), child);
    if (it != children.end()) {
        children.erase(it);
    }
}

std::string Entity::GetName() const {
    return name;
}

string Entity::GetDescription() const {
    return description;
}

shared_ptr<Entity> Entity::GetParent() const {
    return parent;
}

const vector<shared_ptr<Entity>>& Entity::GetChildren() const {
    return children;
}

EntityType Entity::GetType() const {
    return EntityType::ENTITY;
}