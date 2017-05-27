//#pragma once
//#include "MenuScreen.h"
//
//class NavigationButton : public Buton
//{
//public:
//	NavigationButton(int x, int y, SDL_Texture* defaultTexture, SDL_Texture* hoverTexture, SDL_Texture* heldTexture, std::string text, TTF_Font* font, SDL_Color textColor, Mix_Chunk* sound, MenuScreen* gui);
//
//	//Note that the pointer here is to allow the Button to reference its parent, not to add itself in the constructor
//	NavigationButton(pugi::xml_node node, MenuSystem* root);
//
//	MenuScreen* GUIPointer;
//	MenuSystem* parent;
//
//	std::string pointer;
//
//	virtual void mouseDown();
//	virtual void mouseUp();
//};