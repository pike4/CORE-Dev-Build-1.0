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

void MenuLayerAdd::handle(Event e)
{
	switch( e.opcode )
	{
	case mousePress:
		CORE::addGUILayerFromCurrentMenuSystem(source);
		break;

	case mouseRelease:
		break;
	}
}