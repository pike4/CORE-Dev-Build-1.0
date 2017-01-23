#pragma once
#include "ButtonComponent.h"
#include "Definer.h"

class MenuDestination : public Component
{
public:
	MenuDestination();
	MenuDestination(Definer* definer);
	virtual void handleInput(int key, int upDown = 0, int x = 0, int y = 0);

protected:
	std::string destination;
};