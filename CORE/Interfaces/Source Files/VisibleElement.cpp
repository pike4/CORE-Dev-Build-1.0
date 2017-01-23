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

VisibleElement::VisibleElement(Definer* definer)
	:VisibleElement()
{
	//*X = atoi(node.child("x").first_child().value());
	//*Y= atoi(node.child("y").first_child().value());
	w = stoi(definer->getVariable("w"));
	h = stoi(definer->getVariable("h"));

	zIndex = stoi(definer->getVariable("zIndex"));
}


VisibleElement::VisibleElement(VisibleElement& other)
	:VisibleElement()
{
	zIndex = other.zIndex;
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

void VisibleElement::assignPointers(Entity* aParent)
{
	Component::assignPointers(aParent);

	X = (DataOffset<int>*) parent->getCompoundData<DataOffset<int>>("x");
	Y = (DataOffset<int>*) parent->getCompoundData<DataOffset<int>>("y");
}

void VisibleElement::move(int x, int y)
{}