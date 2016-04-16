#pragma once

#include "BaseObject.h"
#include "Updatable.h"
#include "Visible.h"
#include "pugixml.hpp"


class Mobile : public Updatable, public Visible, public BaseObject
{
public:
	virtual void move();

	Mobile(int x, int y, SDL_Texture* texture);
	Mobile(pugi::xml_node, std::vector<BaseObject*>*, std::vector<Visible*>*, std::vector<Updatable*>*);
	~Mobile();

	void setXVel(double value);
	void setYVel(double value);

	int getX();
	int getY();

	int prevX;
	int prevY;

	virtual void draw(SDL_Renderer* renderer);

protected:
	double xVel, yVel;
};