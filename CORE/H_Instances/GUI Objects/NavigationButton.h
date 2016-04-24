#pragma once
#include "Button.h"
#include "MenuScreen.h"

class NavigationButton : public Button
{
public:
	NavigationButton(int x, int y, SDL_Texture* defaultTexture, SDL_Texture* hoverTexture, SDL_Texture* heldTexture, std::string text, TTF_Font* font, SDL_Color textColor, Mix_Chunk* sound, MenuScreen* gui);

	NavigationButton(pugi::xml_node node, MenuSystem* root);

	MenuScreen* GUIPointer;
	MenuSystem* root;

	std::string pointer;

	virtual void mouseDown();
	virtual void mouseUp();
};