#pragma once
#include "MenuSystem.h"
#include "messagePasser.h"
#include "Entity.h"
#include "Control.h"
#include <vector>

class MenuScreen : public Entity, public MessagePasser
{
public:
	MenuScreen() {};
	MenuScreen(XMLNode def);
	MenuScreen(XMLNode def, MenuSystem* root);
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
	void getArgsFromNode(XMLNode def);
	void getArgsFromNode(XMLNode def, MenuSystem* root);
};