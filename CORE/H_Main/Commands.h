#pragma once
#include <string>
#include "SDL.h"
#include "SDL_Mixer.h"

class Command
{
public:
	virtual void execute() = 0;
};

#pragma region StateManager commands
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

#pragma region ObjectManager commands
class walkForwardCommand : public Command
{
public:
	void execute();

	int type;

	walkForwardCommand(int type)
	{
		this->type = type;
	}

};

class walkBackwardCommand : public Command
{
public:

	void execute();

	int type;

	walkBackwardCommand(int type)
	{
		this->type = type;
	}

};

class walkLeftCommand : public Command
{
public:
	
	void execute();

	int type;

	walkLeftCommand(int type)
	{
		this->type = type;
	}

};

class walkRightCommand : public Command
{
public:
	
	void execute();

	int type;

	walkRightCommand(int type)
	{
		this->type = type;
	}

};

class HandleMouseClickCommand : public Command
{
public:

	void execute();

	SDL_Point point;

	HandleMouseClickCommand(int x, int y)
	{
		point.x = x;
		point.y = y;
	}
};

class HandleMouseMoveCommand : public Command
{
	void execute();
};

class HandleMouseUpCommand : public Command
{
	void execute();
};

#pragma endregion

#pragma region SystemManagerCommands
class MouseSendCommand : public Command
{
public:
	SDL_Point point;

	void execute();

	MouseSendCommand(SDL_Point mPoint)
	{
		point.x = mPoint.x;
		point.y = mPoint.y;
	}
};
#pragma endregion