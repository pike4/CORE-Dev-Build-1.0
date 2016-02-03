#pragma once

#include "BaseObject.h"
#include "Updatable.h"
#include "Visible.h"


class Mobile : public Updatable, public Visible, public BaseObject
{
public:
	virtual void move();

	Mobile(int x, int y, SDL_Texture* texture);

	void setXVel(double value);
	void setYVel(double value);

	int getX();
	int getY();

protected:
	double xVel, yVel;
};