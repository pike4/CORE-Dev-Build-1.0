#include "CORE_Audio.h"
#include "SDL_Mixer.h"
#include <string>

namespace CORE_Audio
{
	void handleEvent(int eventCode, int posOrNeg, int x, int y)
	{

	}

	bool start()
	{
		if (SDL_INIT_AUDIO < 0)
		{
			//TODO log error instead
			printf("SDL Audio initialization failed");
			return false;
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			//TODO log error instead
			printf("Failed to open SDL_Audio\n");
			return false;
		}

		return true;
	}

	Mix_Music* loadMusic(char* filename)
	{
		Mix_Music* musicToLoad = Mix_LoadMUS(filename);

		if (musicToLoad == NULL)
		{
			printf("Could not load file %s", filename);
			printf(filename);
		}

		return musicToLoad;
	}

	Mix_Chunk* loadChunk(char* filename)
	{
		Mix_Chunk* chunkToLoad = Mix_LoadWAV(filename);

		if (chunkToLoad == NULL)
		{
			printf("Could not load file %s", filename);
			printf(filename);
		}

		return chunkToLoad;
	}

	void startMusicLoop(Mix_Music* track)
	{
		Mix_PlayMusic(track, -1);
	}

	void pauseMusic()
	{
		Mix_PauseMusic();
	}

	void resumeMusic()
	{
		Mix_ResumeMusic();
	}

	void playSound(Mix_Chunk* sound)
	{
		Mix_PlayChannel(-1, sound, 0);
	}
}
