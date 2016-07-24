#include "CheckBoxButton.h"
#include "EventManager.h"
#include "pugixml.hpp"
#include "SystemManager.h"


CheckBoxButton::CheckBoxButton(pugi::xml_node node)
	:Control(node)
{
	defaultImage_Checked = SystemManager::assignTexture((char*)node.child("DefTexture_Checked").first_child().value());
	heldImage_Checked = SystemManager::assignTexture((char*)node.child("HeldTexture_Checked").first_child().value());
	hoverImage_Checked = SystemManager::assignTexture((char*)node.child("HoverTexture_Checked").first_child().value());

	defaultImage_Unchecked = SystemManager::assignTexture((char*)node.child("DefTexture_Unchecked").first_child().value());
	heldImage_Unchecked = SystemManager::assignTexture((char*)node.child("HeldTexture_Unchecked").first_child().value());
	hoverImage_Unchecked = SystemManager::assignTexture((char*)node.child("HoverTexture_Unchecked").first_child().value());


	realTime = !strcmp(node.child("realTime").first_child().value(), "true");
}

void CheckBoxButton::handleInput(int keyCode, int upDown, int x, int y)
{
	Control::handleInput(keyCode, upDown, x, y);
}

void CheckBoxButton::mouseEnter()
{
	mouseHovering = true;
}

void CheckBoxButton::mouseLeave()
{
	mouseHovering = false;
}

void CheckBoxButton::mouseDown()
{
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
		submit();
	}

	heldImage_Current->texture = heldImage_Checked;
	hoverImage_Current->texture = hoverImage_Checked;
	defaultImage_Current->texture = defaultImage_Checked;
}

void CheckBoxButton::uncheck()
{

	checked = false;
	if (realTime)
	{
		submit();
	}

	heldImage_Current->texture = heldImage_Unchecked;
	hoverImage_Current->texture = hoverImage_Unchecked;
	defaultImage_Current->texture = defaultImage_Unchecked;
}

void CheckBoxButton::submit()
{
	*dataBinding = checked;
}