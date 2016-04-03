#pragma once
#include "Button.h"
#include <vector>

class GUI
{
public:

	GUI();

	std::vector<Button*> buttons;

	void checkMousePos();
	void checkMouseDown();
	void checkMouseUp();

	void add(Button* buttonsToAdd[], int numButtons);
	void add(Button* buttonToAdd);
};