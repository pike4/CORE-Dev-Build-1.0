#pragma once
#include "Mobile.h"
#include "Collidable.h"
#include "Drawable.h"
#include "Controllable.h"
#include "SDL.h"
#include <stack>

class Player : public Mobile, public Collidable, public Controllable
{
public:
	//Player(int x, int y, int w, int h, SDL_Texture* texture);

	Player(pugi::xml_node node, std::vector<BaseObject*>*, std::vector<Drawable*>*, std::vector<Updatable*>*, std::vector<Collidable*>*, std::vector<Controllable*>*);

	void walkUp(int type);
	void walkDown(int type);
	void walkLeft(int type);
	void walkRight(int type);

	virtual void handleInput(int key, int upDown = 0, int x = 0, int y = 0);

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
	virtual void onCollide(Door*);

private:
	double walkSpeed;


};