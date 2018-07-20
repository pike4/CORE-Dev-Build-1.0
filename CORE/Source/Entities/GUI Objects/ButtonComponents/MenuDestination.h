#pragma once
#include "ButtonComponent.h"
#include "DefaultNode.h"

class MenuDestination : public Component
{
public:
	MenuDestination();

	virtual void getText(DefaultNode* def);

   virtual void handle(Event e);

protected:
	std::string destination;
};