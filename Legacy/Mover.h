#pragma once
#include "Component.h"
#include "Controllable.h"

class Mover : public Component, public Controllable
{
public:
	virtual void updatePos() {};
	virtual void addTo(GameObject* object);
	Mover* spawnCopy() = 0;
};