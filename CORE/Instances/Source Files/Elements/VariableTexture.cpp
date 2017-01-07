#include "VariableElement.h"
#include "VideoManager.h"
#include "ObjectManager.h"

VariableElement::VariableElement()
	:VisibleElement()
{
}

VariableElement::VariableElement(pugi::xml_node node) 
	: VariableElement()
{
	pugi::xml_node tempNode = node.first_child();
	std::string name = tempNode.name();
	std::string elemName = "";

	while (!name.empty())
	{
		VisibleElement* newElement = ObjectManager::generateVisibleElement(name, tempNode);
		pugi::xml_node nameNode = tempNode.child("name");
		elemName = tempNode.name();

		//Assign pointers from this to the contained 
		if (newElement && !elemName.empty())
		{
			newElement->X = X;
			newElement->Y = Y;

			elements[elemName] = newElement;
		}
		tempNode = tempNode.next_sibling();
		name = tempNode.name();
	}

	current = elements[elemName];
}

VariableElement::VariableElement(VariableElement& other)
	: VariableElement()
{
	for each (std::pair<std::string, VisibleElement*> entry in elements)
	{
		elements[entry.first] = (VisibleElement*) entry.second->spawnCopy();
	}
}

Component* VariableElement::spawnCopy()
{
	return new VariableElement(*this);
}

void VariableElement::draw()
{
	if (current)
	{
		if (!current->X)
		{
			current->X = X;
			current->Y = Y;
		}

		current->draw();
	}
}

void VariableElement::handleInput(int key, int upDown, int x, int y)
{
	switch (key)
	{
	case drawStep:
		draw();
		break;
	}
}

void VariableElement::setTexture(std::string name)
{
	if (elements.find(name) != elements.end())
	{
		current = elements[name];
	}
}