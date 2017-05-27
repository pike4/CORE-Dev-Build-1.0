#include "MenuLayerAdd.h"
#include "CORE.h"

MenuLayerAdd::MenuLayerAdd()
{
	events.push_back(mousePress);
	events.push_back(mouseRelease);
}

void MenuLayerAdd::getText(Node* def)
{
	source = def->getVariable("source");
}

void MenuLayerAdd::handleInput(int key, int upDown, int x, int y)
{
	switch( key)
	{
	case mousePress:
		CORE::addGUILayerFromCurrentMenuSystem(source);
		break;

	case mouseRelease:
		break;
	}
}