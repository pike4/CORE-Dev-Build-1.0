#pragma once
#include <string>
#include "SDL_Mixer.h"

class Command
{
public:
	virtual void execute() = 0;
};


#pragma region AudioManager commands
class PlayCommand : public Command
{
public:
	void execute();

	PlayCommand(Mix_Chunk* sound)
	{
		this->sound = sound;
	}

	Mix_Chunk* sound;
};

class ChangeMusicCommand : public Command
{
	void execute();

	Mix_Music* track;

	ChangeMusicCommand(Mix_Music* aTrack)
	{
		track = aTrack;
	}
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

#pragma region ObjectManager commands
class walkForwardCommand : public Command
{
public:
	void execute();

	walkForwardCommand(){}

};

class walkBackwardCommand : public Command
{
public:
	void execute();

	walkBackwardCommand(){}

};

class walkLeftCommand : public Command
{
public:
	void execute();

	walkLeftCommand(){}

};

class walkRightCommand : public Command
{
public:
	void execute();

	walkRightCommand(){}

};

#pragma endregion