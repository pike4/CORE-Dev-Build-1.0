#include "CORE_Audio.h"
#include "CORE_Resources.h"
#include "SDL_Mixer.h"

#include <string>

std::map<std::string, Mix_Chunk*> sounds;
std::map<std::string, Mix_Music*> music;

namespace CORE_Audio
{
	Mix_Chunk* getSound(std::string name)
	{
		Mix_Chunk* ret = NULL;

		if (sounds.find(name) != sounds.end()) {
			ret = sounds[name];
		}
		else {
			CORE_SystemIO::error("Sound " + name + " not found");
		}

		return ret;
	}

	Mix_Music* getMusic(std::string name)
	{
		Mix_Music* ret = NULL;

		if (music.find(name) != music.end()) {
			ret = music[name];
		}
		else {
			CORE_SystemIO::error("Music track " + name + " not found");
		}

		return ret;
	}

	void handle(Event e)
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

	Mix_Music* loadMusic(std::string filename)
	{
		Mix_Music* musicToLoad = Mix_LoadMUS(filename.c_str());

		if (musicToLoad == NULL)
		{
			CORE_SystemIO::error("Could not load music file " + filename);
		}

		return musicToLoad;
	}

	Mix_Chunk* loadSound(std::string filename)
	{
		Mix_Chunk* chunkToLoad = Mix_LoadWAV(filename.c_str());

		if (chunkToLoad == NULL)
		{
			CORE_SystemIO::error("Could not load sound file " + filename);
		}

		return chunkToLoad;
	}


	void addTrack(std::string trackName, std::string filename)
	{
		if (music.find(trackName) != music.end())
		{
			CORE_SystemIO::error("Track " + trackName + " already loaded");
			return;
		}

		Mix_Music* newTrack = loadMusic(filename);
		
		if (newTrack)
		{
			music[trackName] = newTrack;
		}
	}

	void addSound(std::string soundName, std::string filename)
	{
		if (sounds.find(soundName) != sounds.end())
		{
			CORE_SystemIO::error("Sound " + soundName + " already loaded");
			return;
		}

		Mix_Chunk* newTrack = loadSound(filename);

		if (newTrack)
		{
			sounds[soundName] = newTrack;
		}
	}

	void startMusicLoop(std::string name)
	{
		Mix_Music* track = getMusic(name);

		if(track)
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

	void playSound(std::string name)
	{
		Mix_Chunk* toPlay = getSound(name);

		if (toPlay)
			Mix_PlayChannel(-1, toPlay, 0);
	}
}
