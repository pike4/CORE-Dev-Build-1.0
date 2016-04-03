#include "NavigationButton.h"
#include "ObjectManager.h"
#include "VideoManager.h"

NavigationButton::NavigationButton(int x, int y, SDL_Texture* defaultTexture, SDL_Texture* hoverTexture, SDL_Texture* heldTexture, std::string text, TTF_Font* font, SDL_Color textColor, Mix_Chunk* sound, GUI* gui)
	:Button(x, y, defaultTexture, hoverTexture, heldTexture, text, font, textColor, sound)
{
	this->GUIPointer = gui;
}

void NavigationButton::mouseDown()
{
	genericMouseDown();

	if(GUIPointer != NULL)
	{
		ObjectManager::currentGUI = GUIPointer;
		VideoManager::currentGUI = GUIPointer;
	}
}

void NavigationButton::mouseUp()
{
	genericMouseUp();
}