#include "CheckBoxButton.h"
#include "EventManager.h"
#include "pugixml.hpp"
#include "SystemManager.h"


CheckBoxButton::CheckBoxButton(pugi::xml_node node)
	:Control(node)
{
	events.push_back(drawStep);
	realTime = !strcmp(node.child("realTime").first_child().value(), "true");
}

void CheckBoxButton::handleInput(int keyCode, int upDown, int x, int y)
{
	Control::handleInput(keyCode, upDown, x, y);
}

void CheckBoxButton::mouseEnter()
{
	defaultImage_Current->texture = hoverImage_Checked;
	mouseHovering = true;
}

void CheckBoxButton::mouseLeave()
{
	defaultImage_Current->texture = defaultImage_Checked;
	mouseHovering = false;
}

void CheckBoxButton::mouseDown()
{
	defaultImage_Current->texture = heldImage_Checked;
	mouseIsDown = true;
}

void CheckBoxButton::mouseUp()
{
	if (checked)
	{
		uncheck();
	}

	else
	{
		check();
	}

	mouseIsDown = false;

	if (realTime)
	{
		*dataBinding = checked;
	}
}

void CheckBoxButton::check()
{
	checked = true;
	if (realTime)
	{
		//submit();
	}

	defaultImage_Current->texture = defaultImage_Checked;
}

void CheckBoxButton::uncheck()
{

	checked = false;
	if (realTime)
	{
		//submit();
	}

	defaultImage_Current->texture = defaultImage_Unchecked;
}

void CheckBoxButton::submit()
{
	*dataBinding = checked;
}