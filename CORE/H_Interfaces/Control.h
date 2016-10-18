#pragma once
#include "Entity.h"
#include "Drawable.h"
#include "SDL.h"
#include "pugixml.hpp"
#include "VisibleElement.h"

class Aggregate;
class MenuScreen;

class Control : public Entity
{
public:
	SDL_Rect box;
	Control(pugi::xml_node node, std::vector<BaseObject*>* objectVector, std::vector<Drawable*>* visibleVector);
	Control(pugi::xml_node node, Aggregate* parent);
	Control(pugi::xml_node node, MenuScreen* parent);
	Control(pugi::xml_node node);

	Control(int x, int y, int w, int h);

	virtual void handleInput(int keyCode, int upDown = 0, int x = 0, int y = 0);

	int getX();
	int getY();

	virtual void move(int x, int y, bool relative = true);
protected:
	bool isWithin(int x, int y);

	void getArgsFromNode(pugi::xml_node node);

	std::vector<VisibleElement*> elements;

	bool mouseHovering;
	bool mouseIsDown;

	bool cancelInputOnMouseLeave = false;
};