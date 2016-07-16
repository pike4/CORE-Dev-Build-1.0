#pragma once
#include "Collidable.h"
#include "Visible.h"
#include "BaseObject.h"
#include "Timer.h"
#include "Updatable.h"
#include "TextObjects.h"
#include <string>
#include "SDL_Mixer.h"
#include "Control.h"

class Button : public Control
{
public:
	//Button(int x, int y, SDL_Texture* defaultTexture, SDL_Texture* hoverTexture, SDL_Texture* heldTexture, std::string text, TTF_Font* font, SDL_Color color,  Mix_Chunk* sound);

	Button(pugi::xml_node node);

	Button(pugi::xml_node, Aggregate* parent);

	void update();

	SDL_Texture* mTexture;

	int textXOffset, textYOffset;

	void draw(SDL_Renderer* renderer);

	bool isWithin(int x, int y);

	SDL_Texture* defaultTexture;
	SDL_Texture* hoverTexture;
	SDL_Texture* heldTexture;

	SDL_Texture* buttonText;

	Mix_Chunk* pressSound;

	virtual void handleInput(int keyCode, int upDown = 0, int x = 0, int y = 0);

	void genericMouseHover();
	void genericMouseLeave();

	void genericMouseDown();
	void genericMouseUp();

private:
	virtual void mouseEnter();
	virtual void mouseLeave();


	virtual void mouseDown();
	virtual void mouseUp();

	// already implemented. no longer needs coding.
	// made this change because some people might think that these functions 
	// still need to be coded, but they don't. trying to save time. above AND below.

	bool mouseIsWithin;
	bool mouseButtonIsHeld;
};