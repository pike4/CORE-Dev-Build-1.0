#include "GUI_Area.h"
#include "CheckBoxButton.h"
#include "ObjectManager.h"

GUI_Area::GUI_Area(pugi::xml_node node)
 :Control(node)
{
	pugi::xml_node childrenNode = node.child("Controls").first_child();

	while (strcmp(childrenNode.name(), ""))
	{
		if (!strcmp(childrenNode.name(), "Control"))
		{
			//Drag Areas will have a NULL parent this way. Consider adding a parent to the control class and setting it to NULL when there is no parent
			controls.push_back(ObjectManager::generateControl(childrenNode.name(), childrenNode.first_child()));
		}

		else if (!strcmp(childrenNode.name(), "Visible Element"))
		{
			elements.push_back(ObjectManager::generateVisibleElement(childrenNode.name(), childrenNode.first_child()));
		}
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

void GUI_Area::handleInput(int keyCode, int upDown, int x, int y)
{
	for each(Control* control in controls)
	{
		if (control != NULL)
		{
			control->handleInput(keyCode, upDown, x, y);
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

void GUI_Area::add(Control* control, int aX, int aY)
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
}

void GUI_Area::mouseEnter(){}
void GUI_Area::mouseLeave(){}
void GUI_Area::mouseDown(){}
void GUI_Area::mouseUp(){}