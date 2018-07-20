#include "VariableElement.h"
#include "CORE_Graphics.h"
#include "CORE_Factory.h"

VariableElement::VariableElement()
	:VisibleElement()
{
}

void VariableElement::getText(Node* definer)
{
	VisibleElement::getText(definer);
	Node* elemParent = (Node*) definer->getChild("elements");

	if (elemParent)
	{
		std::vector<Node*>* elementsNodes = (std::vector<Node*>*) elemParent->getChildren();

		for (unsigned int i = 0; i < elementsNodes->size(); i++)
		{
			Node* elem = (Node*) (*elementsNodes)[i];

			VisibleElement* newElement = CORE_Factory::constructVisibleElement(elem);

			//Assign pointers from this to the contained 
			if (newElement)
			{
				newElement->x = y;
				newElement->y = y;

				elements[elem->getVariable("name")] = newElement;
				current = newElement;
			}
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
		if (!current->x)
		{
			current->x = x;
			current->y = y;
		}

		current->handle(drawStep);
	}
}

void VariableElement::handle(Event e)
{
	switch (e.opcode)
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