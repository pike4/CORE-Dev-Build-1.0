#pragma once
#include "Collidable.h"
#include "QuadTree.h"
#include "MessagePasser.h"
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

class Room : public MessagePasser, public Controllable
{
public:
	std::vector<Controllable*>* controllableVector;

	void spawn(std::string objectName);

	void add(Entity* object);

	void remove(Controllable* component);

	std::string name;

	virtual void handle(Event e);
	virtual void receive(Event e);
	virtual void direct(Event e, Entity* ancestor);

	void draw();

	void update();

	Room(XMLNode def);
	Room(std::string fileName);

	QuadTree* quadTree;

private:
	std::vector<Entity*> entityQueue;

	void emptyQueue();

	void insertEntity(Entity* newEntity);

	void getArgsFromNode(XMLNode def);
	int w, h;
};