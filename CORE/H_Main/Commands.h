#pragma once
#include <string>

class Command
{
public:
	virtual void execute() = 0;
};


#pragma region SoundManager commands
class PlayCommand : public Command
{
public:
	void execute();
};

#pragma endregion


#pragma region VideoManager commands
class FlashCommand : public Command
{
public:
	void execute();

	std::string b;

	FlashCommand(std::string butt)
	{
		b = butt;
	}
};

#pragma endregion