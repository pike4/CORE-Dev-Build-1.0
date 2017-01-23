#include "GUI_Area.h"
#include "CheckBoxButton.h"
#include "CORE_Factory.h"
#include "Entity.h"
#include <string>

GUI_Area::GUI_Area(Definer* definer)
 :Control(definer)
{
	events.push_back(drawStep);
	
	Definer* controlsParent = definer->getChild("controls");
	if (controlsParent)
	{
		std::vector<Definer*>* controlsVector = controlsParent->getChildren();

		for (unsigned int i = 0; i < controlsVector->size(); i++)
		{
			Definer* cur = (*controlsVector)[i];

			Control* newControl = CORE_Factory::generateControl(cur);

			if (newControl)
			{
				components.push_back(newControl);
			}
		}
	}

	Definer* elementsParent = definer->getChild("elements");
	if (controlsParent)
	{
		std::vector<Definer*>* controlsVector = controlsParent->getChildren();

		for (unsigned int i = 0; i < controlsVector->size(); i++)
		{
			Definer* cur = (*controlsVector)[i];

			VisibleElement* newElement = CORE_Factory::generateVisibleElement(cur);

			if (newElement)
			{
				components.push_back(newElement);
			}
		}
	}

	*x = stoi(definer->getVariable("x"));
	*y = stoi(definer->getVariable("y"));
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

void GUI_Area::handleInput(int keyCode, int upDown, int aX, int aY)
{
	Control::handleInput(keyCode, upDown, aX, aY);
}

void GUI_Area::mouseEnter(){}
void GUI_Area::mouseLeave(){}
void GUI_Area::mouseDown(){}
void GUI_Area::mouseUp(){}