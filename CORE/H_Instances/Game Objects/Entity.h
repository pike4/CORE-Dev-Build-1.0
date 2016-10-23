#pragma once
#include <vector>
#include "Component.h"
#include "Updatable.h"
#include "Controllable.h"
#include "Drawable.h"
#include "BaseObject.h"
#include "pugixml.hpp"

#include <map>

class Room;

class Entity : public Component
{
public:
	Entity(pugi::xml_node node);
	Entity(Entity& other);
	Entity() {};

	//Hashtable of data publicly accessible by components
	std::map<std::string, void*> data;

	//Maps event codes to vectors of Controllable objects that listen for those events
	std::map<int, std::vector<Controllable*>*> listeners;

	//The components that make up this object
	std::vector<Component*> components;

	virtual void handleInput(int key, int upDown = 0, int x = 0, int y = 0);

	void add(Component* component);

	//Listeners
	int registerListener(int key, Controllable* listener);
	int deregisterListener(int key, Controllable* listener);

	//Return a pointer to the data at the specified key, allocating with the specified size if it 
	//is not already present in the table
	void* getPointer(std::string key, int size);
	void getPointer(field& pointer);
	void move(int aX, int aY);
private:
	void getArgsFromNode(pugi::xml_node node);

	//
	std::string type;
};