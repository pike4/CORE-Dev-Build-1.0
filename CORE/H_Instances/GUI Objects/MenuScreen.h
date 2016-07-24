#pragma once
#include "MenuSystem.h"
#include "Controllable.h"
#include "Control.h"
#include "Drawable.h"
#include "Updatable.h"
#include <vector>

class MenuScreen : public Updatable, public Drawable, public Controllable
{
public:

	MenuScreen();

	MenuScreen(pugi::xml_node node);
	MenuScreen(pugi::xml_node node, MenuSystem* root);
	MenuScreen(char* fileName);

	std::vector<Control*> controls;

	std::string name;

	void checkMousePos(int x, int y);
	void checkMouseDown(int x, int y);
	void checkMouseUp(int x, int y);

	virtual void draw(SDL_Renderer* renderer);
	virtual void update();
	virtual void handleInput(int key, int upDown = 0, int x = 0, int y = 0);

	void add(Control* controlsToAdd[], int numButtons);
	void add(Control* controlToAdd);

private:
	void getArgsFromNode(pugi::xml_node node);
	void getArgsFromNode(pugi::xml_node node, MenuSystem* root);
};