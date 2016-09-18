#pragma once
#include "Component.h"

class MotionAffector : public Component
{
public:
	virtual int getXContribution() = 0;
	virtual int getYContribution() = 0;
};