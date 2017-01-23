#pragma once
#include "Component.h"
#include "Velocity.h"
#include "Definer.h"

////////////////////////
//Should stay in 
///////////////////////
//SHOULD STAY IN WHAT?
class I_VelocityControl : public Velocity
{
public:
	I_VelocityControl(I_VelocityControl& other);
	I_VelocityControl(Definer* node);
	void assignPointers(Entity* parent);
	virtual void handleInput(int key, int upDown = 0, int x = 0, int y = 0);
	virtual Component* spawnCopy();

private:
};