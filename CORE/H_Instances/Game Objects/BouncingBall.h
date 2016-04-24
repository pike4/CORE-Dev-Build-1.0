#pragma once
#include "Mobile.h"
#include "Collidable.h"
#include "SDL.h"
#include "Player.h"

class Cursor;

class BouncingBall : public Mobile, public Collidable
{
public:
	BouncingBall(int x, int y, int w, int h, SDL_Texture* m_Texture);
	BouncingBall(int x, int y, int w, int h, double xVel, double yVel, SDL_Texture* m_Texture);
	BouncingBall(pugi::xml_node, std::vector<BaseObject*>*, std::vector<Visible*>*, std::vector<Updatable*>*, std::vector<Collidable*>*);
	void update();
	virtual void draw(SDL_Renderer* renderer);
	virtual ~BouncingBall();

	void onCollide(Player* h);
	void onCollide(BouncingBall* h);
	void onCollide(Cursor* h);
};