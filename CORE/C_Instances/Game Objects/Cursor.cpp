#include "Collidable.h"
#include "BaseObject.h"
#include "Cursor.h"
#include "Player.h"
#include "BouncingBall.h"
#include <stdio.h>

Cursor::Cursor(int x, int y, int w, int h) : BaseObject(x, y), Collidable(x, y, w, h)
{
	collidableType = cCursor;
}

void Cursor::onCollide(Player* P)
{
	printf("Cursor is pointing at Player at x: %d, y: %d\n", P->boundingBox.x, P->boundingBox.y);
}

void Cursor::onCollide(BouncingBall* B)
{
	printf("Cursor is pointing at BouncingBall at x: %d, y: %d\n", B->x, B->y);
}

void Cursor::onCollide(Cursor* C)
{

}