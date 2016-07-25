#pragma once

#include "BaseObject.h"
#include "Updatable.h"
#include "pugixml.hpp"
#include "Drawable.h"
#include "SimpleDrawable.h"

class Room;


class Mobile : public Updatable, public SimpleDrawable, public BaseObject
{
public:
	virtual void updatePos();

	Mobile(pugi::xml_node, std::vector<BaseObject*>*, std::vector<Drawable*>*, std::vector<Updatable*>*);
	Mobile(pugi::xml_node, Room* room);
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