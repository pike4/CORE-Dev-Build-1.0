#include "CompositeEnemy.h"
#include "Room.h"

CompositeEnemy::CompositeEnemy(pugi::xml_node node, Room* room)
: BaseObject(node, room), Updatable(room), Collidable(node, room), CompositeDrawable(node, room)
{
	prevXPtr = &x;
	prevYPtr = &y;
}

void CompositeEnemy::update()
{
	move(x, y);
}

void CompositeEnemy::onCollide(BouncingBall*){}
void CompositeEnemy::onCollide(Player*){}
void CompositeEnemy::onCollide(Cursor*){}
void CompositeEnemy::onCollide(Door*) {}