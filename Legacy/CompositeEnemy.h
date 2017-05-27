#pragma once
#include "CompositeDrawable.h"
#include "BaseObject.h"
#include "Collidable.h"
#include "Updatable.h"

class Room;

class CompositeEnemy : public BaseObject, public CompositeDrawable, public Updatable, public Collidable
{
public:

	CompositeEnemy(pugi::xml_node node);
	CompositeEnemy(pugi::xml_node, Room* room);
	CompositeEnemy(CompositeEnemy& other);
	CompositeEnemy(CompositeEnemy& other, Room* room);

	virtual BaseObject* spawnCopy(Room* room);
	
	virtual void update();
	virtual void onCollide(BouncingBall*);
	virtual void onCollide(Player*);
	virtual void onCollide(Cursor*);
	virtual void onCollide(Door*);
};