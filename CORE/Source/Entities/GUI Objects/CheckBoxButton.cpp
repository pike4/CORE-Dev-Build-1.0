#include "CheckBoxButton.h"
#include "CORE_Devices.h"
#include "CORE_Resources.h"

void CheckBoxButton::getText(Node* def)
{
}

void CheckBoxButton::handleInput(int keyCode, int upDown, int x, int y)
{
	this;
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
}

void CheckBoxButton::check()
{
	checked = true;


	defaultImage_Current->texture = defaultImage_Checked;
}

void CheckBoxButton::uncheck()
{

	checked = false;

	defaultImage_Current->texture = defaultImage_Unchecked;
}

void CheckBoxButton::submit()
{
	*dataBinding = checked;
}