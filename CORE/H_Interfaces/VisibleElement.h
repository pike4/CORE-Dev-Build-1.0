#pragma once
#include "Drawable.h"
#include "pugixml.hpp"
#include "SDL.h"
#include "RenderableCharSet.h"

class VisibleElement : public Drawable, public Component
{
public:
	int parentOffsetX, parentOffsetY;
	SDL_Rect box;
	VisibleElement(int x, int y, int w, int h);
	VisibleElement(pugi::xml_node node);
	VisibleElement(VisibleElement& copy);

	virtual void move(int x, int y);

	virtual Component* spawnCopy();
	virtual void addTo(Room* room);
};