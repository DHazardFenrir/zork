#pragma once
#ifndef __Entity__
#define __Entity__

#include <string>
#include <vector>
#include <memory>
#include <iostream>
using namespace std;


class Entity
{
public:
	Entity(const std::string& name, const std::string& description, std::shared_ptr<Entity> parent = nullptr);
	virtual ~Entity();
	virtual void Look() const;
	void AddChild(std::shared_ptr<Entity> child);
	void RemoveChild(std::shared_ptr<Entity> child);
	const std::vector<std::shared_ptr<Entity>>& GetChildren() const;

protected:
	std::string name;
	std::string description;
	std::vector<shared_ptr<Entity>> children;

};
#endif // !__Entity__
