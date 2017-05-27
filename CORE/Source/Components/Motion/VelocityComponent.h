#pragma once

#include "MotionAffector.h"
#include <vector>
#include "pugixml.hpp"

class VelocityComponent
{
public:
	VelocityComponent(pugi::xml_node node);

	virtual void move(int x, int y);

	virtual void updatePos();
	virtual void handleInput(int keyCode, int upDown = false, int x = 0, int y = 0);
	//virtual Mover* spawnCopy();

private:
	double xVel, yVel;
};