#pragma once
#include "Drawable.h"
#include "pugixml.hpp"
#include "SDL.h"
#include "RenderableCharSet.h"

class VisibleElement : public Drawable, public Component
{
public:
	int parentOffsetX, parentOffsetY;

	int* x;
	int* y;
	int w;
	int h;

	VisibleElement();
	VisibleElement(int x, int y, int w, int h);
	VisibleElement(pugi::xml_node node);
	VisibleElement(VisibleElement& copy);

	virtual void handleInput(int key, int upDown = 0, int x = 0, int y = 0);

	virtual void move(int x, int y);

	virtual Component* spawnCopy() = 0;
	virtual void addTo(Room* room);
};