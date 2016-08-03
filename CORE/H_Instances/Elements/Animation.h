#pragma once
#include "VisibleElement.h"
#include "Timer.h"

class Animation : public VisibleElement
{
public:
	virtual void draw(SDL_Renderer* renderer);
	Animation(pugi::xml_node node);

private:
	VisibleElement** frames;

	//The number of frames in the animation
	int numFrames;

	//The index of the current frame being drawn
	int frameIndex;

	//Used to tell when it is time to draw a new frame
	Timer frameTimer;

	//
	unsigned int millisecondsPerFrame;

	virtual void move(int x, int y);
};