#pragma once
#include "VisibleElement.h"
#include "Timer.h"

class Animation : public VisibleElement
{
public:
	virtual void draw();
	Animation();

	Animation(Animation& other);

	virtual void getText(XMLNode def);

	virtual VisibleElement* spawnCopy();
	virtual void handle(Event e);
private:
	VisibleElement** frames;

	//The number of frames in the animation
	unsigned int numFrames;

	//The index of the current frame being drawn
	unsigned int frameIndex;

	//Used to tell when it is time to draw a new frame
	Timer frameTimer;

	//
	unsigned int millisecondsPerFrame;

	virtual void move(int x, int y);
};