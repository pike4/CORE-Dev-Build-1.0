#include "SpeechBox.h"
#include "CORE_Resources.h"
#include "CORE_Audio.h"
#include "CORE_Graphics.h"
#include <string>

SpeechBox::SpeechBox(int aW, int aH, char* message, SDL_Texture* background, 
	RenderableCharSet* characterSet) : Control()
{
	x = new DataImpl<int>(CORE_TypeTraits::TR_SIMPLE);
	y = new DataImpl<int>(CORE_TypeTraits::TR_SIMPLE);
	w = aW;
	h = aH;

	charSet = characterSet;

	textTimer = Timer();
	frequency = 50;
	variation = 70;

	charToLines(message);
}

SpeechBox::SpeechBox(DefaultNode* def)
{
	frequency = stoi(def->getVariable("frequency"));
	variation = stoi(def->getVariable("variation"));
}

void SpeechBox::update()
{
	if (textTimer.hasElapsed(curWaitTime))
	{
		curWaitTime = rand() % variation + frequency;

		if (characterIndex < lines[firstLineIndex].length() - 1)
		{
			characterIndex++;
			CORE_Audio::playSound(CORE_Resources::assignSound("Assets/Music/talk_sample_1.wav"));
		}

		else if (lastLineIndex < maxLines - 1)
		{
			characterIndex = 0;
			lastLineIndex++;
		}

		else if ((lastLineIndex - firstLineIndex >= maxLines) 
			&& lastLineIndex < maxLines - 1)
		{
			characterIndex = 0;
			firstLineIndex++;
			lastLineIndex++;
		}
		textTimer.updateTime();
	}
}

void SpeechBox::charToLines(char* message)
{
	int length = strlen(message);
	unsigned short curLineWidth = 0;
	unsigned short curWordWidth = 0;
	unsigned short curCharWidth = 0;
	unsigned short curLineIndex = 0;
	lines.push_back("");
	std::string curWord = "";

	//Convert given char* to vector of char* words
	for (int x = 0; x < length; x++)
	{
		curCharWidth = charSet->fontWidth(message[x]);
		if (message[x] != ' ')
		{
			curWord += message[x];
			curWordWidth += curCharWidth;
		}

		else if (curWord.compare(""))
		{
			//Add the current word to the line if it fits
			if ((curLineWidth + curWordWidth) <= w)
			{
				curLineWidth += curWordWidth;
				lines.back() += " " + curWord;
			}

			//Otherwise, add it to a new line, splitting as needed
			else
			{
				lines.push_back("");
				curLineWidth = 0;
				for (unsigned int i = 0; i < curWord.length(); i++)
				{
					lines.back() += curWord[i];
					curLineWidth += charSet->fontWidth(curWord[i]);
					if (curLineWidth >= w)
					{
						lines.push_back("");
						curLineWidth = 0;
					}
				}
			}
			curWord = "";
			curWordWidth = 0;
		}
	}

	//And push the leftover word onto the stack
	if (curWord.compare(""))
	{
		words.push_back(curWord);
	}
	curWord = "";

	if (curWord.compare(""))
	{
		lines.push_back(curWord);
	}

	words.clear();

	for each (std::string curString in lines)
	{
		printf("%s\n",curString.c_str());
	}

	maxLines = lines.size();
}

void SpeechBox::handle(Event e)
{
	switch (e.opcode)
	{
	case interactButtonDown:
		break;
	case drawStep:
		draw();
		break;
	case updateStep:
		update();
		break;
	}
}

void SpeechBox::draw()
{
	int penX = *x;
	int penY = *y;

	for (int i= firstLineIndex; i <= lastLineIndex; i++)
	{
		for (unsigned int j = 0; j < lines[i].length(); j++)
		{
			if (i == lastLineIndex && j == characterIndex)
			{
				break;
			}
			char curChar = lines[i][j];
			CORE_Graphics::addDraw(penX, penY, (*charSet)[curChar], zIndex );
			penX += charSet->fontWidth(curChar);
		}
		penX = 0;
		penY += charSet->fontHeight;
	}
}

void SpeechBox::start()
{
	textTimer.updateTime();
	writing = true;
}

void SpeechBox::clear()
{
	messageIndex = 0;
	characterIndex = 0;
	firstLineIndex = 0;
	lastLineIndex = 0;
	currentLineWidth = 0;
	currentLineHeight = 0;
	maxLineLength = 0;
	maxLines = 0;

	words.empty();
	lines.empty();
	writing = false;
}

void SpeechBox::print(char* message)
{
	clear();
	charToLines(message);
	start();
}

void SpeechBox::print(char* message, RenderableCharSet* newCharSet)
{
	charSet = newCharSet;
	print(message);
}