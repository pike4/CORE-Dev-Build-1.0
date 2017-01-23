#include "MenuDestination.h"
#include "CORE.h"


MenuDestination::MenuDestination() : Component()
{
	events.push_back(mousePress);
	events.push_back(mouseRelease);
}

MenuDestination::MenuDestination(Definer* definer) : MenuDestination()
{
	destination = definer->getVariable("destination");
}

void MenuDestination::handleInput(int key, int upDown, int x, int y)
{
	switch (key)
	{
	case mousePress:
		CORE::goToGUIInCurrentMenuSystem(destination);
		break;
	case mouseRelease:
		break;
	}
}