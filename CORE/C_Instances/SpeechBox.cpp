#include "SpeechBox.h"
#include "Subject.h"
#include "SystemManager.h"
#include "EventManager.h"

//SpeechBox::SpeechBox(int x, int y, char* message, SDL_Texture* background, RenderableCharSet* characterSet)
//{
//	charSet = characterSet;
//
//	textTimer = Timer();
//	waitTime = 50;
//
//	charToLines(message);
//}

void SpeechBox::update()
{
	if (textTimer.hasElapsed(waitTime))
	{
		if (characterIndex < lines[firstLineIndex].length() - 1)
		{
			characterIndex++;
		}

		else
		{
			characterIndex = 0;
			if (lastLineIndex < maxLines)
			{
				lastLineIndex++;

				if (lastLineIndex - firstLineIndex > maxLines)
				{
					firstLineIndex++;
				}
			}
		}
	}
}

void SpeechBox::charToLines(char* message)
{
	maxLineLength = 20;
	int length = strlen(message);

	std::string curWord = "";

	//Convert given char* to vector of char* words
	for (int x = 0; x < length; x++)
	{
		if (message[x] != ' ')
		{
			curWord += message[x];
		}

		else if (curWord.compare(""))
		{
			words.push_back(curWord);
			curWord = "";
		}
	}

	if (curWord.compare(""))
	{
		words.push_back(curWord);
	}
	curWord = "";

	//Push down words onto lines vector so they wrap
	for (int x = 0; x < words.size(); x++)
	{
		if (words[x].length() + curWord.length() < maxLineLength)
		{
			curWord += words[x] + " ";
		}

		else if(words[x].length() < maxLineLength)
		{
			lines.push_back(curWord);
			curWord = "";
			x--;
		}

		else
		{
			lines.push_back(curWord.substr(0, maxLineLength));

		}
	}

	if (curWord.compare(""))
	{
		lines.push_back(curWord);
	}

	words.clear();

	for each (string curString in lines)
	{
		printf("%s\n",curString.c_str());
	}
}

void SpeechBox::handleInput(int key, int upDown, int x, int y)
{
	switch (key)
	{
	case interactButtonDown:
		break;
	}
}

int SpeechBox::getX()
{
	return x;
}

int SpeechBox::getY()
{
	return y;
}

void SpeechBox::draw(SDL_Renderer* renderer)
{
	Visible::draw(renderer);

	int penX = 0;
	int penY = 0;

	for (int x = firstLineIndex; x <= lastLineIndex; x++)
	{
		for (int y = 0; y < lines[x].length(); y++)
		{
			VideoManager::applyTexture(penX, penY, renderer, charSet->charSet[lines[x][y]]);
			penX += charSet->fontWidth;
		}

		penY += charSet->fontHeight;
	}
}