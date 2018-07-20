#pragma once
#include "ButtonComponent.h"
#include "Node.h"

class MenuDestination : public Component
{
public:
	MenuDestination();

	virtual void getText(Node def);

   virtual void handle(Event e);

protected:
	std::string destination;
};