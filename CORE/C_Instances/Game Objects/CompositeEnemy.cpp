#include "CompositeEnemy.h"
#include "Room.h"

CompositeEnemy::CompositeEnemy(pugi::xml_node node)
	: BaseObject(node), Updatable(), Collidable(node), CompositeDrawable(node)
{
	prevXPtr = &x;
	prevYPtr = &y;
}

CompositeEnemy::CompositeEnemy(pugi::xml_node node, Room* room)
: BaseObject(node, room), Updatable(room), Collidable(node, room), CompositeDrawable(node, room)
{
	prevXPtr = &x;
	prevYPtr = &y;
}

CompositeEnemy::CompositeEnemy(CompositeEnemy& other)
	:BaseObject(other), CompositeDrawable(other), Collidable(other)
{}

CompositeEnemy::CompositeEnemy(CompositeEnemy& other, Room* room)
	:BaseObject(other, room), Updatable(room), Collidable(other, room), CompositeDrawable(other, room)
{

}

void CompositeEnemy::update()
{
//	move(x, y);
}

BaseObject* CompositeEnemy::spawnCopy(Room* room)
{
	return new CompositeEnemy(*this, room);
}

void CompositeEnemy::onCollide(BouncingBall*){}
void CompositeEnemy::onCollide(Player*){}
void CompositeEnemy::onCollide(Cursor*){}
void CompositeEnemy::onCollide(Door*) {}