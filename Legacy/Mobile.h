#pragma once

#include "BaseObject.h"
#include "Updatable.h"
#include "pugixml.hpp"
#include "Drawable.h"
#include "SimpleDrawable.h"

class Room;


class Mobile : public BaseObject, public Updatable
{
public:
	virtual void updatePos();

	Mobile(pugi::xml_node, std::vector<BaseObject*>*);
	Mobile(pugi::xml_node, Room* room);
	Mobile(pugi::xml_node);
	~Mobile();

	void setXVel(double value);
	void setYVel(double value);

	int getX();
	int getY();

	int prevX;
	int prevY;

	virtual void move(int x, int y);
	virtual void addTo(Room* room);
	virtual void update();

protected:
	double xVel, yVel;
};