#include "NavigationButton.h"
#include "ObjectManager.h"
#include "VideoManager.h"

NavigationButton::NavigationButton(int x, int y, SDL_Texture* defaultTexture, SDL_Texture* hoverTexture, SDL_Texture* heldTexture, std::string text, TTF_Font* font, SDL_Color textColor, Mix_Chunk* sound, MenuScreen* gui)
	:Button(x, y, defaultTexture, hoverTexture, heldTexture, text, font, textColor, sound)
{
	this->GUIPointer = gui;
}

NavigationButton::NavigationButton(pugi::xml_node node, MenuSystem* root)
	:Button(node)
{
	pointer = node.child("pointer").first_child().value();
	this->root = root;
}

void NavigationButton::mouseDown()
{
	genericMouseDown();


	
}

void NavigationButton::mouseUp()
{
	genericMouseUp();
	genericMouseLeave();
	ObjectManager::currentGUI = root->menus[pointer];
	VideoManager::currentGUI = root->menus[pointer];
}