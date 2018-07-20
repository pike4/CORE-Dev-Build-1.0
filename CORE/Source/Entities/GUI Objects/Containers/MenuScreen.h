#pragma once
#include "MenuSystem.h"
#include "Entity.h"
#include "Control.h"
#include <vector>

class MenuScreen : public Entity
{
public:
	MenuScreen() {};
	MenuScreen(DefaultNode* def);
	MenuScreen(DefaultNode* def, MenuSystem* root);
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
	void getArgsFromNode(DefaultNode* def);
	void getArgsFromNode(DefaultNode* def, MenuSystem* root);
};