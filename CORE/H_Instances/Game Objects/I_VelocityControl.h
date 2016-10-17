#pragma once
#include "Component.h"
#include "pugixml.hpp"

////////////////////////
//Should stay in 
///////////////////////

class I_VelocityControl : public Component
{
public:
	I_VelocityControl(I_VelocityControl& other);
	I_VelocityControl(pugi::xml_node node);
	void assignPointers(GameObject* parent);
	virtual void handleInput(int key, int upDown = 0, int x = 0, int y = 0);
	virtual Component* spawnCopy();
	virtual void move(int x, int y);

private:
	int* x;
	int* y;
	
	double* xVel;
	double* yVel;
};