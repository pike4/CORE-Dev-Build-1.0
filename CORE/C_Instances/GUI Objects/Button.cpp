#include "Collidable.h"
#include "SystemManager.h"
#include "Visible.h"
#include "BaseObject.h"
#include "Button.h"
#include "Updatable.h"
#include "QuadTree.h"
#include "TextObjects.h"
#include "AudioManager.h"
#include "VideoManager.h"
#include <string.h>

Button::Button(int x, int y, SDL_Texture* defaultTexture, SDL_Texture* hoverTexture, SDL_Texture* heldTexture, std::string text, TTF_Font* font, SDL_Color textColor, Mix_Chunk* sound) :
	BaseObject(x, y), Updatable()
{
	this->mTexture = defaultTexture;
	this->defaultTexture = defaultTexture;
	this->heldTexture = heldTexture;
	this->hoverTexture = hoverTexture;
	this->w = w;
	this->h = h;
	SDL_QueryTexture(defaultTexture, NULL, NULL, &this->w, &this->h);
	this->pressSound = sound;
	if (strcmp(text.c_str(), "") != 0 && font != NULL)
	{
		this->buttonText = SDL_CreateTextureFromSurface(VideoManager::mRenderer, TTF_RenderText_Solid(font, text.c_str(), textColor));

		int textWidth, textHeight;

		TTF_SizeText(font, _strdup(text.c_str()), &textWidth, &textHeight);

		textXOffset = (w - textWidth) / 2;
		textYOffset = (h - textWidth * 9 / 16) / 2;
	}

	else
	{
		this->buttonText = NULL;
	}
}

Button::Button(pugi::xml_node node)
	:BaseObject(node), Updatable()
{
	int fontSize;
	char* text;
	TTF_Font* font;

	printf("%s\n", node.name());
	x = atoi(node.child("x").first_child().value());
	y = atoi(node.child("y").first_child().value());
	w = atoi(node.child("w").first_child().value());
	h = atoi(node.child("h").first_child().value());

	defaultTexture = SystemManager::assignTexture((char*)node.child("DefTexture").first_child().value());
	heldTexture = SystemManager::assignTexture((char*)node.child("HeldTexture").first_child().value());
	hoverTexture= SystemManager::assignTexture((char*)node.child("HoverTexture").first_child().value());
	pressSound = SystemManager::assignSound((char*)node.child("pressSound").first_child().value());
	text = (char*)node.child("text").first_child().value();
	fontSize = atoi(node.child("fontSize").first_child().value());
	font = SystemManager::assignFont((char*)node.child("font").first_child().value(), fontSize);

	SDL_Color col;
	col.a = 20;

	buttonText = SDL_CreateTextureFromSurface(VideoManager::mRenderer, TTF_RenderText_Solid(font, text, col));
	mTexture = defaultTexture;

	SDL_QueryTexture(defaultTexture, NULL, NULL, &(this->w), &(this->h));

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

void Button::draw(SDL_Renderer* renderer)
{
	VideoManager::applyTexture(x, y, renderer, mTexture);

	if (buttonText != NULL)
	{
		VideoManager::applyTexture(x + textXOffset, y + textYOffset, VideoManager::mRenderer, buttonText);
	}
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
	genericMouseHover();
}

void Button::mouseLeave()
{
	genericMouseLeave();
}

void Button::mouseDown()
{
	genericMouseDown();
}

void Button::mouseUp()
{
	genericMouseUp();
}

void Button::genericMouseHover()
{
	mouseIsWithin = true;
	if (mTexture != heldTexture)
	{
		mTexture = hoverTexture;
	}
}

void Button::genericMouseLeave()
{
	mouseIsWithin = false;
	mTexture = defaultTexture;
}

void Button::genericMouseDown()
{
	mouseButtonIsHeld = true;
	mTexture = heldTexture;

	if (pressSound != NULL)
	{
		AudioManager::enqueue(new PlayCommand(this->pressSound));
	}
}

void Button::genericMouseUp()
{
	mouseButtonIsHeld = false;
	mTexture = hoverTexture;
}