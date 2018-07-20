#pragma once
#include "Component.h"
#include "Velocity.h"
#include "DefaultNode.h"

////////////////////////
//Should stay in 
///////////////////////
//SHOULD STAY IN WHAT?
class I_VelocityControl : public Velocity
{
public:
	I_VelocityControl();
	I_VelocityControl(I_VelocityControl& other);
	virtual void handle(Event e);
	virtual Component* spawnCopy();

private:
};