#pragma once
#include "Button.h"
#include "GUI.h"

class NavigationButton : public Button
{
public:
	NavigationButton(int x, int y, SDL_Texture* defaultTexture, SDL_Texture* hoverTexture, SDL_Texture* heldTexture, std::string text, TTF_Font* font, SDL_Color textColor, Mix_Chunk* sound, GUI* gui);

	GUI* GUIPointer;

	virtual void mouseDown();
	virtual void mouseUp();
};