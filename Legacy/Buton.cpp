//#include "Collidable.h"
//#include "SystemManager.h"
//#include "Visible.h"
//#include "BaseObject.h"
//#include "Button.h"
//#include "Updatable.h"
//#include "QuadTree.h"
//#include "TextObjects.h"
//#include "AudioManager.h"
//#include "VideoManager.h"
//#include <string.h>
//#include "Aggregate.h"
//
////Button::Button(int x, int y, SDL_Texture* defaultTexture, SDL_Texture* hoverTexture, SDL_Texture* heldTexture, std::string text, TTF_Font* font, SDL_Color textColor, Mix_Chunk* sound) :
////	Control()
////{
////	this->mTexture = defaultTexture;
////	this->defaultTexture = defaultTexture;
////	this->heldTexture = heldTexture;
////	this->hoverTexture = hoverTexture;
////	this->w = w;
////	this->h = h;
////	SDL_QueryTexture(defaultTexture, NULL, NULL, &this->w, &this->h);
////	this->pressSound = sound;
////	if (strcmp(text.c_str(), "") != 0 && font != NULL)
////	{
////		this->buttonText = SDL_CreateTextureFromSurface(VideoManager::mRenderer, TTF_RenderText_Solid(font, text.c_str(), textColor));
////
////		int textWidth, textHeight;
////
////		TTF_SizeText(font, _strdup(text.c_str()), &textWidth, &textHeight);
////
////		textXOffset = (w - textWidth) / 2;
////		textYOffset = (h - textWidth * 9 / 16) / 2;
////	}
////
////	else
////	{
////		this->buttonText = NULL;
////	}
////}
//
//Buton::Buton(pugi::xml_node node)
//	: Control(node)
//{
//	int fontSize;
//	char* text;
//	TTF_Font* font;
//
//	printf("%s\n", node.name());
//
//	defaultTexture = SystemManager::assignTexture((char*)node.child("DefTexture").first_child().value());
//	heldTexture = SystemManager::assignTexture((char*)node.child("HeldTexture").first_child().value());
//	hoverTexture= SystemManager::assignTexture((char*)node.child("HoverTexture").first_child().value());
//	pressSound = SystemManager::assignSound((char*)node.child("pressSound").first_child().value());
//	text = (char*)node.child("text").first_child().value();
//	fontSize = atoi(node.child("fontSize").first_child().value());
//	font = SystemManager::assignFont((char*)node.child("font").first_child().value(), fontSize);
//
//	SDL_Color col;
//	col.a = 20;
//
//	buttonText = SDL_CreateTextureFromSurface(VideoManager::mRenderer, TTF_RenderText_Solid(font, text, col));
//	mTexture = defaultTexture;
//
//	SDL_QueryTexture(defaultTexture, NULL, NULL, &(this->box.w), &(this->box.h));
//
//}
//
//Buton::Buton(pugi::xml_node node, Aggregate* parent) : Buton(node)
//{
//	parent->addChild(this);
//}
//
//void Buton::update()
//{
//
//}
//
//void Buton::draw(SDL_Renderer* renderer)
//{
//	VideoManager::applyTexture(box.x, box.y, renderer, mTexture);
//
//	if (buttonText != NULL)
//	{
//		VideoManager::applyTexture(box.x + textXOffset, box.y + textYOffset, VideoManager::mRenderer, buttonText);
//	}
//}
//
//void Buton::mouseEnter()
//{
//	genericMouseHover();
//}
//
//void Buton::mouseLeave()
//{
//	genericMouseLeave();
//}
//
//void Buton::mouseDown()
//{
//	genericMouseDown();
//}
//
//void Buton::mouseUp()
//{
//	genericMouseUp();
//}
//
//void Buton::genericMouseHover()
//{
//	mouseIsWithin = true;
//	if (mTexture != heldTexture)
//	{
//		mTexture = hoverTexture;
//	}
//}
//
//void Buton::genericMouseLeave()
//{
//	mouseIsWithin = false;
//	mTexture = defaultTexture;
//}
//
//void Buton::genericMouseDown()
//{
//	mouseButtonIsHeld = true;
//	mTexture = heldTexture;
//
//	if (pressSound != NULL)
//	{
//		AudioManager::enqueue(new PlayCommand(this->pressSound));
//	}
//}
//
//void Buton::genericMouseUp()
//{
//	mouseButtonIsHeld = false;
//	mTexture = hoverTexture;
//}
//
//void Buton::handleInput(int keyCode, int upDown, int x, int y)
//{
//
//}