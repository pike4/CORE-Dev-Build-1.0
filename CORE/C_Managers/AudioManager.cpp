#include "AudioManager.h"
#include "SDL_Mixer.h"
#include <string>


int AudioManager::state;

bool AudioManager::start()
{
	if (SDL_INIT_AUDIO < 0)
	{
		printf("SDL Audio initialization failed");
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("Failed to open SDL_Audio\n");
		return false;
	}
	
	
	else return true;
}

#pragma region State Transitions

void AudioManager::goToRunning()
{
	state = CORE_RUNNING;
}

void AudioManager::goToBlocking()
{
	state = CORE_BLOCKING;
}

void AudioManager::goToInMenu()
{
	state = CORE_IN_MENU;
}

void AudioManager::goToPaused()
{
	state = CORE_PAUSED;
}
#pragma endregion

Mix_Music* AudioManager::loadMusic(char* filename)
{
	Mix_Music* musicToLoad = Mix_LoadMUS(filename);

	if (musicToLoad == NULL)
	{
		printf("Could not load file %c", filename);
		printf(filename);
	}
	
	return musicToLoad;
}

Mix_Chunk* AudioManager::loadChunk(char* filename)
{
	Mix_Chunk* chunkToLoad = Mix_LoadWAV(filename);

	if (chunkToLoad == NULL)
	{
		printf("Could not load file %c", filename);
		printf(filename);
	}

	return chunkToLoad;
}

void AudioManager::startMusicLoop(Mix_Music* track)
{
	Mix_PlayMusic(track, -1);
}

void AudioManager::pauseMusic()
{
	Mix_PauseMusic();
}

void AudioManager::resumeMusic()
{
	Mix_ResumeMusic();
}


void AudioManager::playSound(Mix_Chunk* sound)
{
	Mix_PlayChannel(-1, sound, 0);
}

void AudioManager::update()
{
	updateQueue();
}


#pragma region Commands
void PlayCommand::execute()
{
	AudioManager::playSound(sound);
}

void ChangeMusicCommand::execute()
{
	AudioManager::startMusicLoop(track);
}

void PauseMusicCommand::execute()
{
	AudioManager::pauseMusic();
}

void ResumeMusicCommand::execute()
{
	AudioManager::resumeMusic();
}
#pragma endregion
