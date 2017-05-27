#pragma once
#include "ButtonComponent.h"
#include "Node.h"

class MenuDestination : public Component
{
public:
	MenuDestination();

	virtual void getText(Node* def);

	virtual void handleInput(int key, int upDown = 0, int x = 0, int y = 0);

protected:
	std::string destination;
};