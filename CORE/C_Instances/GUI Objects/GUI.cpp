#include "GUI.h"
#include "ObjectManager.h"
#include <vector>

GUI::GUI()
{
	//buttons = std::vector();
}

void GUI::checkMousePos()
{
	if (ObjectManager::currentGUI != NULL)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];

			if (button->isWithin(x, y))
			{
				button->mouseHover();
			}

			else
			{
				button->mouseLeave();

				printf("Mouse x: %d, y: %d\n ", x, y);
			}
		}
	}
}

void GUI::add(Button buttonsToAdd[], int numButtons)
{
	for (int i = 0; i < numButtons; i++)
	{
		buttons.push_back(&buttonsToAdd[i]);
	}
}

void GUI::add(Button* buttonToAdd)
{
		buttons.push_back(buttonToAdd);
}

void GUI::checkMouseDown()
{
	if (ObjectManager::currentGUI != NULL)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];

			if (button->isWithin(x, y))
			{
				button->mouseDown();
			}

		}
	}
}

void GUI::checkMouseUp()
{
	if (ObjectManager::currentGUI != NULL)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];

			if (button->isWithin(x, y))
			{
				button->mouseUp();
			}
		}
	}
}