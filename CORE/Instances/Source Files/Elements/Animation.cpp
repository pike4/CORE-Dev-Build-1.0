#include "Animation.h"
#include "VideoManager.h"

Animation::Animation(pugi::xml_node node)
 : VisibleElement(node)
{
	std::string fileName = node.child("fileName").first_child().value();
	millisecondsPerFrame = atoi(node.child("millisecondsPerFrame").first_child().value());
	int frameH = atoi(node.child("frameH").first_child().value());
	int frameW = atoi(node.child("frameW").first_child().value());
	int framesX = atoi(node.child("framesX").first_child().value());
	int framesY = atoi(node.child("framesY").first_child().value());
	int seperation = atoi(node.child("seperation").first_child().value());

	frames = new VisibleElement*[framesX * framesY];
	numFrames = framesX * framesY;
	
	VideoManager::getAnimationFromSpriteSheet(framesX, framesY, frameW, frameH, seperation, fileName, frames);
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

	if (!frames[frameIndex]->x)
	{
		frames[frameIndex]->x = x;
		frames[frameIndex]->y = y;
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

void Animation::handleInput(int key, int upDown, int x, int y)
{
	switch (key)
	{
	case drawStep:
		draw();
		break;
	}
}