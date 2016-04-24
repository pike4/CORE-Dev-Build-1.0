#pragma once
#include <string>
#include "MenuScreen.h"
class ManagerArgs
{
public:
	int state;
};

class VideoManagerArgs : public ManagerArgs
{
public:
	int screenWidth, screenHeight, screenX, screenY;
	std::string windowCaption;
	bool fullscreen;
	SDL_Color defaultFillColor;
};

class AudioManagerArgs : public ManagerArgs
{
public:

};

class SystemManagerArgs : public ManagerArgs
{

};

class ObjectManagerArgs : public ManagerArgs
{
public:
	MenuScreen* initialGUI;
};