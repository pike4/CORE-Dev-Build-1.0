#pragma once
#include "Collidable.h"
#include "BaseObject.h"

class Player;
class BouncingBall;

class Cursor : public BaseObject, public Collidable
{
public:
	Cursor(int x, int y, int w, int h);

	void onCollide(Player*);
	void onCollide(BouncingBall*);
	void onCollide(Cursor*);
};