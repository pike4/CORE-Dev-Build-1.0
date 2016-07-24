#pragma once
#include "Updatable.h"
#include "Controllable.h"
#include "Timer.h"
#include "RenderableCharSet.h"
#include "Aggregate.h"

class SpeechBox : public Aggregate, public Updatable
{
public:

	SpeechBox(int x, int y, char*, SDL_Texture*, RenderableCharSet*);

	virtual void handleInput(int key, int upDown = 0, int x = 0, int y = 0);

	virtual void update();
	virtual int getX();
	virtual int getY();
	virtual void draw(SDL_Renderer*);

	void show();
	void hide();

	char* message;
	RenderableCharSet* charSet;

	int maxLineLength;
	int maxLines;

	void charToLines(char* message);

	RenderableCharacter** currentMessage;

private:
	//The timer used to determine how quickly to type out the current message
	Timer textTimer;

	//The width in pixels of all characters in the current line
	int currentLineWidth;

	//The height of the tallest character in the line
	int currentLineHeight;

	//The index of the message currently being typed out or displayed
	unsigned short messageIndex;

	//The index of the character in the current message being typed out
	unsigned short characterIndex;

	//The index of the first line to display in the pane
	unsigned short firstLineIndex;

	//The index of the last line to display in the pane
	unsigned short lastLineIndex;

	//The amount of time between writing out characters
	int waitTime;
	std::vector<std::string> words;
	std::vector<std::string> lines;
};