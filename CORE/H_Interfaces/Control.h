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
	int w;
	int h;

	int* x;
	int* y;

	Control();
	Control(pugi::xml_node node, std::vector<BaseObject*>* objectVector, std::vector<Drawable*>* visibleVector);
	Control(pugi::xml_node node, Aggregate* parent);
	Control(pugi::xml_node node, MenuScreen* parent);
	Control(pugi::xml_node node);

	Control(int x, int y, int w, int h);

	virtual void handleInput(int keyCode, int upDown = 0, int x = 0, int y = 0);

	//Enable or disable the control for drawing
	void show();
	void hide();

	Control* parent;

protected:
	bool isWithin(int x, int y);

	void getArgsFromNode(pugi::xml_node node);

	std::vector<VisibleElement*> elements;

	bool mouseHovering;
	bool mouseIsDown;

	bool cancelInputOnMouseLeave = false;

	bool hidden;
};