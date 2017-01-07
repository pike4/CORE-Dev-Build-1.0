#include "GUI_Area.h"
#include "CheckBoxButton.h"
#include "ObjectManager.h"
#include "Entity.h"

GUI_Area::GUI_Area(pugi::xml_node node)
 :Control(node)
{
	events.push_back(drawStep);
	pugi::xml_node tempNode = node.first_child();
	std::string name = tempNode.name();
	
	while (!name.empty())
	{
		if (!name.compare("Controls"))
		{
			pugi::xml_node node2 = tempNode.first_child();
			while (strcmp(node2.name(), ""))
			{
				Control* newControl = ObjectManager::generateControl(node2.name(), node2);

				if (newControl)
				{
					components.push_back(newControl);
					newControl->parent = this;
				}

				node2 = node2.next_sibling();
			}
		}

		else if (!name.compare("Elements"))
		{
			pugi::xml_node node2 = tempNode.first_child();
			while (strcmp(node2.name(), ""))
			{
				VisibleElement* newElem = ObjectManager::generateVisibleElement
					(node2.name(), node2);

				if (newElem)
				{
					components.push_back(newElem);
				}
				node2 = node2.next_sibling();
			}
		}

		else if (!name.compare("x"))
		{
			*x = atoi(tempNode.first_child().value());
		}

		else if (!name.compare("y"))
		{
			*y = atoi(tempNode.first_child().value());
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

void GUI_Area::handleInput(int keyCode, int upDown, int aX, int aY)
{
	Control::handleInput(keyCode, upDown, aX, aY);
}

void GUI_Area::mouseEnter(){}
void GUI_Area::mouseLeave(){}
void GUI_Area::mouseDown(){}
void GUI_Area::mouseUp(){}