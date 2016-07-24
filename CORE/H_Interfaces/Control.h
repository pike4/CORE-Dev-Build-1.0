#pragma once
#include "BaseObject.h"
#include "Controllable.h"
#include "Drawable.h"
#include "Updatable.h"
#include "SDL.h"
#include "pugixml.hpp"
#include "VisibleElement.h"

class Aggregate;
class MenuScreen;

class Control : public Controllable, public Drawable, public Updatable
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

	virtual void update();

	virtual void draw(SDL_Renderer* renderer);
	virtual void move(int x, int y, bool relative = true);
protected:
	virtual void mouseEnter() = 0;
	virtual void mouseLeave() = 0;
	virtual void mouseDown() = 0;
	virtual void mouseUp() = 0;

	bool isWithin(int x, int y);

	void getArgsFromNode(pugi::xml_node node);

	std::vector<VisibleElement*> elements;

	bool mouseHovering;
	bool mouseIsDown;

	bool cancelInputOnMouseLeave = false;
};