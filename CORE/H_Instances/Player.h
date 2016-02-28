#pragma once
#include "Mobile.h"
#include "Collidable.h"
#include "SDL.h"
#include <stack>

class Player : public Mobile, public Collidable
{
public:
	Player(int x, int y, int w, int h, SDL_Texture* texture);

	void walkUp(int type);
	void walkDown(int type);
	void walkLeft(int type);
	void walkRight(int type);

	void popWalkUp(int type);
	void popWalkDown(int type);
	void popWalkLeft(int type);
	void popWalkRight(int type);

	bool walkingUp;
	bool walkingDown;
	bool walkingLeft;
	bool walkingRight;

	std::stack<int> xDirectionStack;
	std::stack<int> yDirectionStack;

	void move();
	void update();

private:
	double walkSpeed;


};