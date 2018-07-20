#include "MenuDestination.h"
#include "CORE.h"


MenuDestination::MenuDestination() : Component()
{
	events.push_back(mousePress);
	events.push_back(mouseRelease);
}

void MenuDestination::getText(DefaultNode* def)
{
	destination = def->getVariable("destination");
}

void MenuDestination::handle(Event e)
{
	switch (e.opcode)
	{
	case mousePress:
		CORE::goToGUIInCurrentMenuSystem(destination);
		break;
	case mouseRelease:
		break;
	}
}