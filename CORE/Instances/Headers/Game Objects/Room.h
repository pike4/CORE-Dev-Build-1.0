#pragma once
#include "Updatable.h"
#include "BaseObject.h"
#include "Drawable.h"
#include "Collidable.h"
#include "QuadTree.h"
#include "Controllable.h"
#include "Drawable.h"
#include "Pugixml.hpp"
#include <vector>

class  Entity;

class Room : public Updatable, public Drawable, public Controllable
{
public:

	std::vector<Updatable*>* updateVector;
	std::vector<Drawable*>* drawVector;
	std::vector<BaseObject*>* objectVector;
	std::vector<Collidable*>* collidableVector;
	std::vector<Controllable*>* controllableVector;

	void spawn(std::string objectName);

	void add(Entity* object);
	void add(Updatable* component);
	void add(Drawable* component);
	void add(BaseObject* component);
	void add(Collidable* component);
	void add(Controllable* component);

	void remove(Entity* object);
	void remove(Updatable* component);
	void remove(Drawable* component);
	void remove(BaseObject* component);
	void remove(Collidable* component);
	void remove(Controllable* component);

	std::string name;

	void handleInput(int key, int posOrNeg = 0, int x = 0, int y = 0);

	void draw();

	void update();

	Room(pugi::xml_node);
	Room(std::string fileName);

	QuadTree* quadTree;

private:
	void getArgsFromNode(pugi::xml_node node);
	int w, h;
};