#pragma once
#include "Position.h"

class Velocity : public Position
{
public:
	Velocity();
	Velocity(pugi::xml_node node);
	Velocity(Velocity&);
	virtual Component* spawnCopy();
	virtual void move(int aX, int aY);
	void assignPointers(GameObject* parent);

	virtual void handleInput(int key, int upDown = 0, int aX = 0, int aY = 0);

protected:
	double* xVel;
	double* yVel;
};