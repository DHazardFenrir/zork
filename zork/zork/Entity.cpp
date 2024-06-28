#include "Entity.h"

Entity::Entity(const string& name, const string& description, shared_ptr<Entity> parent)
    : name(name), description(description), parent(parent) {}

Entity::~Entity() {}

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

string Entity::GetName() const {
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
    return EntityType::ENTITY
}