#pragma once
#include "MenuSystem.h"
#include "Entity.h"
#include "Control.h"
#include <vector>

class MenuScreen : public Entity
{
public:
	MenuScreen() {};
	MenuScreen(Node def);
	MenuScreen(Node def, MenuSystem* root);
	MenuScreen(char* fileName);

	std::string name;

	void checkMousePos(int x, int y);
	void checkMouseDown(int x, int y);
	void checkMouseUp(int x, int y);

	virtual void draw();
	virtual void update();

	void add(Control* controlsToAdd[], int numButtons);
	void add(Control* controlToAdd);

private:
	void getArgsFromNode(Node def);
	void getArgsFromNode(Node def, MenuSystem* root);
};