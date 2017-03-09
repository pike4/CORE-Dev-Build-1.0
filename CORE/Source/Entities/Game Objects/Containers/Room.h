#pragma once
#include "Collidable.h"
#include "QuadTree.h"
#include "Controllable.h"

#include <vector>

class  Entity;

/*
	Provides a single context for the user to interact with the world. Contains and tracks a set
	of Entity objects. Rooms behave in a manner analogous to scenes in Unity or GameMake.
	This is the second level in the interface between CORE and its game objects. No instances of
	game objects apart from prototypes can exist in CORE outside of a room.
*/

class Room : public Controllable
{
public:
	std::vector<Controllable*>* controllableVector;

	void spawn(std::string objectName);

	void add(Entity* object);

	void remove(Entity* object);
	void remove(Controllable* component);

	std::string name;

	void handleInput(int key, int posOrNeg = 0, int x = 0, int y = 0);

	void draw();

	void update();

	Room(Node* def);
	Room(std::string fileName);

	QuadTree* quadTree;

private:
	void getArgsFromNode(Node* def);
	int w, h;
};