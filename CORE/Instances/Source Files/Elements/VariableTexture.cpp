#include "VariableElement.h"
#include "CORE_Graphics.h"
#include "CORE_Factory.h"

VariableElement::VariableElement()
	:VisibleElement()
{
}

VariableElement::VariableElement(Definer* definer)
	: VisibleElement(definer)
{
	std::vector<Definer*>* elementsNodes = definer->getChildren();

	for (unsigned int i = 0; i < elementsNodes->size(); i++)
	{
		Definer* elem = (*elementsNodes)[i];
			
		VisibleElement* newElement = CORE_Factory::generateVisibleElement(elem);

		//Assign pointers from this to the contained 
		if (newElement)
		{
			newElement->X = X;
			newElement->Y = Y;

			elements[elem->getVariable("name")] = newElement;
			current = newElement;
		}
	}
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

		current->handleInput(drawStep);
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