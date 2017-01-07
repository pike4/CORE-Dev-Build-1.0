#include "MenuDestination.h"
#include "StateManager.h"


MenuDestination::MenuDestination() : Component()
{
	events.push_back(mousePress);
	events.push_back(mouseRelease);
}

MenuDestination::MenuDestination(pugi::xml_node node) : MenuDestination()
{
	node = node.child("destination");
	destination = node.first_child().value();
}

void MenuDestination::handleInput(int key, int upDown, int x, int y)
{
	switch (key)
	{
	case mousePress:
		StateManager::goToGUIInCurrentMenuSystem(destination);
		break;
	case mouseRelease:
		break;
	}
}