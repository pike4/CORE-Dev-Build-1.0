#include "Collidable.h"
#include "Visible.h"
#include "BaseObject.h"
#include "Button.h"
#include "Updatable.h"
#include "QuadTree.h"

Button::Button(int x, int y, int w, int h, SDL_Texture* defaultTexture, SDL_Texture* hoverTexture, SDL_Texture* heldTexture) :
	BaseObject(x, y), Visible(defaultTexture), Updatable()
{
	this->defaultTexture = defaultTexture;
	this->heldTexture = heldTexture;
	this->hoverTexture = hoverTexture;
	this->w = w;
	this->h = h;
	SDL_QueryTexture(defaultTexture, NULL, NULL, &this->w, &this->h);
}

int Button::getX()
{
	return x;
}

int Button::getY()
{
	return y;
}

void Button::update()
{

}

void Button::onCollide(Visible* v)
{

}

void Button::onCollide(Player* p)
{
	
}

bool Button::isWithin(int x, int y)
{
	return (x > this->x && x < this->x + this->w && y > this->y && y < this->y + this->h);
}

void Button::onCollide(BouncingBall* b) {}

void Button::onCollide(Cursor* c)
{
		mouseHover();
}

void Button::mouseHover()
{
	mouseIsWithin = true;
	if (mTexture != heldTexture)
	{
		mTexture = hoverTexture;
	}
	
}

void Button::mouseLeave()
{
	mouseIsWithin = false;
	mTexture = defaultTexture;
}

void Button::mouseDown()
{
	mouseButtonIsHeld = true;
	mTexture = heldTexture;
}

void Button::mouseUp()
{
	mouseButtonIsHeld = false;
	mTexture = hoverTexture;
}