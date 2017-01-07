#include "ButtonComponent.h"

ButtonComponent::ButtonComponent()
{
	events.push_back(mousePress);
	events.push_back(mouseRelease);
	events.push_back(mouseDrag);
}