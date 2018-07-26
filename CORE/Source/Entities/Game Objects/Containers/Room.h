#pragma once
#include "Collidable.h"
#include "QuadTree.h"
#include "Controllable.h"
#include "Node.h"

#include <vector>

class  Entity;

/*
	Provides a single context for the user to interact with the world. 
   Contains and tracks a set of Entity objects. Rooms behave similarly 
   to scenes in Unity and GameMaker.
	This is the second level in the interface between CORE and its game objects. 
   No instances of game objects (other than prototypes) can exist in CORE outside 
   of a room.
*/

class Room : public Controllable
{
public:
	std::vector<Controllable*>* controllableVector;

	void spawn(std::string objectName);

	void add(Entity* object);

	void remove(Controllable* component);

	std::string name;

   void handle(Event e);

	void draw();

	void update();

	void registerEvent(int opcode, Controllable* observer);

	void unregisterEvent(int opcode, Controllable* observer);

	Room(XMLNode def);
	Room(std::string fileName);

	QuadTree* quadTree;

private:
	std::vector<Entity*> entityQueue;

	std::map<int, std::vector<Controllable*>> observers;

	void emptyQueue();

	void insertEntity(Entity* newEntity);

	void getArgsFromNode(XMLNode def);
	int w, h;
};