#pragma once
#include "Controllable.h"
#include "Timer.h"
#include "RenderableCharSet.h"
#include "DefaultNode.h"
#include "Control.h"

class SpeechBox : public Control
{
public:

	SpeechBox(int x, int y, char* message, SDL_Texture* background, RenderableCharSet* characterSet);
	SpeechBox(DefaultNode* def);

   virtual void handle(Event e);

	virtual void update();
	virtual void draw();

	void start();
	void clear();

	void print(char* message);
	void print(char* message, RenderableCharSet* newCharSet);

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
	int frequency = 200;

	//The random interval by which to vary the write speed
	int variation;

	//The current time interval to wait for the next character
	int curWaitTime = 0;

	//A vector of individual words so words don't get split across lines
	std::vector<std::string> words;

	//The string is parsed into lines based on the lengths of words
	std::vector<std::string> lines;

	//True if the speechbox is currently being updated
	bool writing;

	//Width and height of the text area
	int w;
	int h;

	//This HAS to go away
	int zIndex = 1;
};