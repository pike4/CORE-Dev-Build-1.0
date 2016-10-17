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

class GameObject : public Controllable
{
public:
	GameObject(pugi::xml_node node);
	GameObject(GameObject& other);

	//Hashtable of data publicly accessible by components
	std::map<std::string, void*> data;

	//Maps event codes to vectors of Controllable objects that listen for those events
	std::map<int, std::vector<Controllable*>*> listeners;

	//The components that make up this object
	std::vector<Component*> components;

	virtual void handleInput(int key, int upDown = 0, int x = 0, int y = 0);
	virtual void move(int x, int y);

	//Listeners
	int registerListener(int key, Controllable* listener);
	int deregisterListener(int key, Controllable* listener);

	//Return a pointer to the data at the specified key, allocating with the specified size if it 
	//is not already present in the table
	void* getPointer(std::string key, int size);

private:
	void getArgsFromNode(pugi::xml_node node);

	//
	std::string type;
};