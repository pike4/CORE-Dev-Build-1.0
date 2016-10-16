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

class GameObject : public Updatable, public Controllable, public BaseObject
{
public:
	GameObject(pugi::xml_node node);
	GameObject(GameObject& other);

	std::map<std::string, long long int> publicData;
	std::map<std::string, void*> data;

	std::map<int, std::vector<Controllable*>*> listeners;

	std::vector<Component*> components;

	Drawable* drawableComponent;

	virtual void handleInput(int key, int upDown = 0, int x = 0, int y = 0);
	virtual void update();
	virtual void move(int x, int y);

	//Listeners
	int registerListener(int key, Controllable* listener);
	int deregisterListener(int key, Controllable* listener);

	void* getPointer(std::string key, int size);

	bool isUpdatable();
	bool isControllable();
	bool isDrawable();

private:
	void getArgsFromNode(pugi::xml_node node);
	bool updatable = false;
	bool controllable = false;

	//
	std::string type;
};