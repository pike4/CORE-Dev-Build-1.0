#pragma once
#include "Control.h"
#include "ImageElement.h"

class CheckBoxButton : public Control
{
public:
	void getText(DefaultNode* def);

	ImageElement* heldImage_Current;
	ImageElement* hoverImage_Current;
	ImageElement* defaultImage_Current;

	SDL_Texture* heldImage_Checked;
	SDL_Texture* heldImage_Unchecked;
	SDL_Texture* hoverImage_Checked;
	SDL_Texture* hoverImage_Unchecked;
	SDL_Texture* defaultImage_Checked;
	SDL_Texture* defaultImage_Unchecked;

   virtual void handle(Event e);

protected:
	bool* dataBinding;
	bool checked;

	virtual void mouseEnter();
	virtual void mouseLeave();
	virtual void mouseDown();
	virtual void mouseUp();

	void check();
	void uncheck();

	virtual void submit();
};