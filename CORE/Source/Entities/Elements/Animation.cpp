#include "Animation.h"
#include "CORE_Graphics.h"

Animation::Animation() {}

void Animation::getText(XMLNode definer)

{
	VisibleElement::getText(definer);
	std::string fileName = definer.getVariable("fileName");
	millisecondsPerFrame =	Util::toInt(definer.getVariable("millisecondsPerFrame"));
	int frameH =			Util::toInt(definer.getVariable("frameH"));
	int frameW =			Util::toInt(definer.getVariable("frameW"));
	int framesX =			Util::toInt(definer.getVariable("framesX"));
	int framesY =			Util::toInt(definer.getVariable("framesY"));
	int seperation =		Util::toInt(definer.getVariable("seperation"));

	frames = new VisibleElement*[framesX * framesY];
	numFrames = framesX * framesY;
	
	CORE_Graphics::getAnimationFromSpriteSheet(framesX, framesY, frameW, frameH, seperation, fileName, frames);
}

Animation::Animation(Animation& other)
	:VisibleElement(other)
{
	numFrames = other.numFrames;
	frames = new VisibleElement*[numFrames];
	for (int i = 0; i < numFrames; i++)
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
	if (!frames[frameIndex]->x)
	{
		frames[frameIndex]->x = x;
		frames[frameIndex]->x = y;
	}

	frames[frameIndex]->draw();
}

void Animation::move(int x, int y)
{
	for (int i = 0; i < numFrames; i++)
	{
		frames[i]->move(x, y);
	}
}

VisibleElement* Animation::spawnCopy()
{
	return new Animation(*this);
}

void Animation::handle(Event e)
{
	switch (e.opcode)
	{
	case drawStep:
		draw();
		break;
	}
}