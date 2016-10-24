#include "GUI_Area.h"
#include "CheckBoxButton.h"
#include "ObjectManager.h"
#include "Entity.h"

GUI_Area::GUI_Area(pugi::xml_node node)
 :Control(node)
{
	events.push_back(drawStep);
	pugi::xml_node tempNode = node.child("Controls").first_child();
	std::string name = tempNode.name();

	while (strcmp(tempNode.name(), ""))
	{
		Control* newControl = ObjectManager::generateControl(name, tempNode);

		if (newControl)
		{
			add(newControl);
		}

		tempNode = tempNode.next_sibling();
		name = tempNode.name();
	}

	tempNode = node.child("Elements").first_child();
	name = tempNode.name();
	while (strcmp(tempNode.name(), ""))
	{
		VisibleElement* newElem = ObjectManager::generateVisibleElement(name, tempNode);

		if (newElem)
		{
			add(newElem);
		}
		tempNode = tempNode.next_sibling();
		name = tempNode.name();
	}
}

GUI_Area::GUI_Area(int x, int y, int w, int h)
	:Control(x, y, w, h)
{

}

void GUI_Area::update()
{
	for each(Control* control in controls)
	{
		if (control != NULL)
		{
			control->handleInput(updateStep);
		}
	}
}

void GUI_Area::draw(SDL_Renderer* renderer)
{
	for each(VisibleElement* element in elements)
	{
		if (element != NULL)
		{
			element->draw();
		}
	}
}

/*void GUI_Area::add(Control* control, int aX, int aY)
{
	if (control == NULL)
	{
		//TODO: log error
		return;
	}

	controls.push_back(control);
	*(control->x) = *x + aX;
	*(control->y) = *y + aY;
}

void GUI_Area::add(VisibleElement* element, int x, int y)
{
	if (element == NULL)
	{
		//TODO: log error
		return;
	}

	//elements.push_back(element);
//	element->box.x = box.x + x;
	//element->box.y = box.y + y;
}*/

void GUI_Area::mouseEnter(){}
void GUI_Area::mouseLeave(){}
void GUI_Area::mouseDown(){}
void GUI_Area::mouseUp(){}