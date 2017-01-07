#pragma once
#pragma once
#include "Drawable.h"
#include "pugixml.hpp"
#include "VisibleElement.h"
#include "SDL.h"
#include <vector>

class Room;

class  CompositeDrawable : public VisibleElement
{
public:
	CompositeDrawable(pugi::xml_node node);
	CompositeDrawable(pugi::xml_node node, Room* room);

	CompositeDrawable(CompositeDrawable& other);
	CompositeDrawable(CompositeDrawable& other, Room* room);

	virtual Component* spawnCopy();

	std::vector<VisibleElement*> elements;
	virtual void draw()
	{
		for (unsigned int i = 0; i < elements.size(); i++)
		{
			elements[i]->draw();
		}
	}

	void move(int x, int y);
};