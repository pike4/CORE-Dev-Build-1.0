#pragma once
#include "VisibleElement.h"
#include "Timer.h"

class Animation : public VisibleElement
{
public:
	virtual void draw();
	Animation(Definer* definer);

	Animation(Animation& other);

	virtual VisibleElement* spawnCopy();
	virtual void handleInput(int key, int upDown = 0, int x = 0, int y = 0);
private:
	VisibleElement** frames;

	//The number of frames in the animation
	unsigned int numFrames;

	//The index of the current frame being drawn
	int frameIndex;

	//Used to tell when it is time to draw a new frame
	Timer frameTimer;

	//
	unsigned int millisecondsPerFrame;

	virtual void move(int x, int y);
};