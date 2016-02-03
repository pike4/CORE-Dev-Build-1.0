#pragma once
#include "Manipulatable.h"
#include "Updatable.h"
#include "BaseObject.h"

class Spinner : public Manipulatable, public Updatable, public BaseObject
{
public:
	void update();
	void rotate(double arotationPerTick);
	void setRotationPerTick(double aRotationPerTick);

	int getX();
	int getY();

	Spinner(int x, int y, SDL_Texture* aTexture, SDL_RendererFlip aFlip, double aRotation, SDL_Point aPoint, double aRotationPerTick);
	Spinner(int x, int y, SDL_Texture* aTexture);

private:
	double rotationPerTick;


};