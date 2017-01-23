#pragma once
#include <string>
#include "SDL.h"
#include "SDL_Mixer.h"

class Command
{
public:
	virtual void execute() = 0;
};

#pragma region CORE commands
class ChangeStateCommand : public Command
{
public:
	void execute();

	int state;

	ChangeStateCommand(int st)
	{
		state = st;
	}
};

#pragma endregion

#pragma region CORE_Audio commands
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
public:
	void execute();

	Mix_Music* track;

	ChangeMusicCommand(Mix_Music* aTrack)
	{
		track = aTrack;
	}
};

class ResumeMusicCommand : public Command
{
public:
	void execute();

	ResumeMusicCommand(){};
};

class PauseMusicCommand : public Command
{
public:
	void execute();

	PauseMusicCommand(){};
};

#pragma endregion

#pragma region CORE_Graphics commands

class DrawRectCommand : public Command
{
public:
	void execute();

	SDL_Rect rect;

	DrawRectCommand(SDL_Rect g)
	{
		rect = g;
	}
};

#pragma endregion