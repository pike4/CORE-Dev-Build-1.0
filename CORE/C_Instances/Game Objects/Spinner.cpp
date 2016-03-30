#include "Spinner.h"
#include "Manipulatable.h"
#include "VideoManager.h"
#include "ObjectManager.h"
void Spinner::update()
{
	Manipulatable::rotate(rotationPerTick);
}

void Spinner::setRotationPerTick(double aRotationPerTick)
{
	rotationPerTick = aRotationPerTick;
}


Spinner::Spinner(int x, int y, SDL_Texture* aTexture, SDL_RendererFlip aFlip, double aRotation, SDL_Point aPoint, double aRotationPerTick)
	: BaseObject(x, y), Manipulatable(aTexture, aFlip, aRotation, aPoint)
{
	rotationPerTick = aRotationPerTick;
}

Spinner::Spinner(int x, int y, SDL_Texture* aTexture, double aRotationPerTick)
	: BaseObject(x, y), Manipulatable(aTexture)
{
	rotationPerTick = aRotationPerTick;
}

Spinner::Spinner(int x, int y, SDL_Texture* aTexture)
	:BaseObject(x, y), Manipulatable(aTexture)
{
	this->rotationPerTick = 0;
}

int Spinner::getX()
{
	return x;
}

int Spinner::getY()
{
	return y;
}