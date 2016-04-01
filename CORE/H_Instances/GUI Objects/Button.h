#pragma once
#include "Collidable.h"
#include "Visible.h"
#include "BaseObject.h"
#include "Timer.h"
#include "Updatable.h"

class Button :  public Visible, public BaseObject, public Updatable
{
public:
	Button(int x, int y, int w, int h, SDL_Texture* defaultTexture, SDL_Texture* hoverTexture, SDL_Texture* heldTexture);

	void onCollide(Visible*);
	void onCollide(Player*);
	void onCollide(Cursor*);
	void onCollide(BouncingBall*);
	void update();

	int w, h;

	int getX();
	int getY();

	bool isWithin(int x, int y);

	SDL_Texture* defaultTexture;
	SDL_Texture* hoverTexture;
	SDL_Texture* heldTexture;

	void mouseHover();
	void mouseLeave();

	void mouseDown();
	void mouseUp();

	bool mouseIsWithin;
	bool mouseButtonIsHeld;
};