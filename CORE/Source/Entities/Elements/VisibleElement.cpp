#include "Component.h"
#include "VisibleElement.h"
#include "CORE_Graphics.h"

#include "pugixml.hpp"
#include "SDL.h"

VisibleElement::VisibleElement()
{
	events.push_back(drawStep);
}

VisibleElement::VisibleElement(int x, int y, int aW, int aH)
	:VisibleElement()
{
	w = aW;
	h = aH;
}

VisibleElement::VisibleElement(VisibleElement& other)
	:VisibleElement()
{
}

void VisibleElement::get_data(DataSource* source)
{
	x = source->getData<int>("x");
	y = source->getData<int>("y");

	zIndex = source->getData<int>("zIndex");
}

void VisibleElement::getText(Node* def)
{
	w = stoi(def->getVariable("w"));
	h = stoi(def->getVariable("h"));
}

void VisibleElement::handleInput(int key, int upDown, int x, int y)
{
	switch (key)
	{
	case drawStep:
		draw();
		break;
	}
}

void VisibleElement::move(int x, int y)
{}