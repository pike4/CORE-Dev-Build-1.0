#include "Animation.h"
#include "CORE_Graphics.h"

Animation::Animation(Definer* definer)
 : VisibleElement(definer)
{
	std::string fileName = definer->getVariable("fileName");
	millisecondsPerFrame = stoi(definer->getVariable("millisecondsPerFrame"));
	int frameH = stoi(definer->getVariable("frameH"));
	int frameW = stoi(definer->getVariable("frameW"));
	int framesX = stoi(definer->getVariable("framesX"));
	int framesY = stoi(definer->getVariable("framesY"));
	int seperation = stoi(definer->getVariable("seperation"));

	frames = new VisibleElement*[framesX * framesY];
	numFrames = framesX * framesY;
	
	CORE_Graphics::getAnimationFromSpriteSheet(framesX, framesY, frameW, frameH, seperation, fileName, frames);
}

Animation::Animation(Animation& other)
	:VisibleElement(other)
{
	numFrames = other.numFrames;
	frames = new VisibleElement*[numFrames];
	for (unsigned int i = 0; i < numFrames; i++)
	{
		frames[i] = (VisibleElement*)other.frames[i]->spawnCopy();
		frames[i]->zIndex = zIndex;
	}

	millisecondsPerFrame = other.millisecondsPerFrame;
}

void Animation::draw()
{
	if (frameTimer.hasElapsed(millisecondsPerFrame))
	{
		if (++frameIndex >= numFrames)
		{
			frameIndex = 0;
		}

		frameTimer.updateTime();
	}

	//Assign this animation's pointers to the frame if its pointers are not already
	//initialized
	if (!frames[frameIndex]->X)
	{
		frames[frameIndex]->X = X;
		frames[frameIndex]->Y = Y;
	}

	frames[frameIndex]->draw();
}

void Animation::move(int x, int y)
{
	for (unsigned int i = 0; i < numFrames; i++)
	{
		frames[i]->move(x, y);
	}
}

VisibleElement* Animation::spawnCopy()
{
	return new Animation(*this);
}

void Animation::handleInput(int key, int upDown, int x, int y)
{
	switch (key)
	{
	case drawStep:
		draw();
		break;
	}
}