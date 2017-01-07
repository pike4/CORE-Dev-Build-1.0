#include "MenuLayerAdd.h"
#include "StateManager.h"

MenuLayerAdd::MenuLayerAdd()
{
	events.push_back(mousePress);
	events.push_back(mouseRelease);
}

MenuLayerAdd::MenuLayerAdd(pugi::xml_node node) : MenuLayerAdd()
{
	node = node.child("source");
	source = node.first_child().value();
}

void MenuLayerAdd::handleInput(int key, int upDown, int x, int y)
{
	switch( key)
	{
	case mousePress:
		StateManager::addGUILayerFromCurrentMenuSystem(source);
		break;

	case mouseRelease:
		break;
	}
}