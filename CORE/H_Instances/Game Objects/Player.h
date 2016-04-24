#pragma once
#include "Mobile.h"
#include "Collidable.h"
#include "SDL.h"
#include <stack>

class Player : public Mobile, public Collidable
{
public:
	Player(int x, int y, int w, int h, SDL_Texture* texture);

	Player(pugi::xml_node node, std::vector<BaseObject*>*, std::vector<Visible*>*, std::vector<Updatable*>*, std::vector<Collidable*>*);

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

	void move();
	void update();

	void onCollide(Collidable*);
	virtual void onCollide(BouncingBall*);
	virtual void onCollide(Player*);
	virtual void onCollide(Cursor*);

private:
	double walkSpeed;


};