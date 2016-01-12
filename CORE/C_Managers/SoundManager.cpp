#include "SoundManager.h"
#include "SDL_Mixer.h"


bool SoundManager::start()
{
	if (SDL_INIT_AUDIO < 0)
	{
		printf("SDL Audio initialization failed");
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL Audio opening failed");
		return false;
	}


	else return true;
}

void SoundManager::update()
{
	updateQueue();
}

void PlayCommand::execute()
{
	printf("Butt");
}
