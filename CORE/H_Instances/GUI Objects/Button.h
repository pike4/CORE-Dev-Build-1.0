#pragma once
#include "Collidable.h"
#include "Visible.h"
#include "BaseObject.h"
#include "Timer.h"
#include "Updatable.h"
#include "TextObjects.h"
#include <string>
#include "SDL_Mixer.h"

class Button : public BaseObject, public Updatable
{
public:
	Button(int x, int y, SDL_Texture* defaultTexture, SDL_Texture* hoverTexture, SDL_Texture* heldTexture, std::string text, TTF_Font* font, SDL_Color color,  Mix_Chunk* sound);

	Button(pugi::xml_node node);

	void onCollide(Visible*);
	void onCollide(Player*);
	void onCollide(Cursor*);
	void onCollide(BouncingBall*);
	void update();

	SDL_Texture* mTexture;

	int w, h;

	int textXOffset, textYOffset;

	int getX();
	int getY();

	void draw(SDL_Renderer* renderer);

	bool isWithin(int x, int y);

	SDL_Texture* defaultTexture;
	SDL_Texture* hoverTexture;
	SDL_Texture* heldTexture;

	SDL_Texture* buttonText;

	Mix_Chunk* pressSound;

	virtual void mouseHover();
	virtual void mouseLeave();

	void genericMouseHover();
	void genericMouseLeave();

	virtual void mouseDown();
	virtual void mouseUp();

	void genericMouseDown();
	void genericMouseUp();

	bool mouseIsWithin;
	bool mouseButtonIsHeld;
};