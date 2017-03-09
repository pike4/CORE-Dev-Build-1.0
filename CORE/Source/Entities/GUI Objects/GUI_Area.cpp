#include "GUI_Area.h"
#include "CheckBoxButton.h"
#include "CORE_Factory.h"
#include "Entity.h"
#include <string>

GUI_Area::GUI_Area()
 :Control()
{
	events.push_back(drawStep);
}

void GUI_Area::get_data(DataSource* source)
{
	Control::get_data(source);
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