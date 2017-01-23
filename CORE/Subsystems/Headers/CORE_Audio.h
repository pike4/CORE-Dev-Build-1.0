#pragma once

#include "SDL.h"
#include "SDL_Mixer.h"
#include "Commands.h"
#include <string>

namespace CORE_Audio
{
	//Initialize audio subsytems
	bool start();

	//TODO: collection of available audio channels
	//std::map<std::string, AudioChannel*> channels;

	//TODO: Initialize a new channel
	//addChannel(std::string name);
	
	//TODO: stop the channel of the given name playing, free it and remove it from CORE_Audio
	//removeChannel(std::string name);

	//TODO: pause the given channel
	//pauseChannel(std::string name);

	//TODO: resume the givenChannel
	//resumeChannel(std::string name);

	//TODO:
	//

	//TODO:
	//

	//TODO: Begin a continuous loop on the sppecified channel
	//StartLoop(string track, string channel);

	//TODO: set the volume for the specified track
	//setVolume(string channel, double volume);

	//TODO: play the given sound on the given track
	//PlaySound(string track, string channel);

	void update();

	void handleEvent(int eventCode, int posOrNeg = 0, int x = 0, int y = 0);


	//These two belong to CORE_Resources
	Mix_Music* loadMusic(char* filename);
	Mix_Chunk* loadChunk(char* filename);

	//Begin a continuous loop of the given Mix_Music. 
	//Delet this, no one should know about SDL Mixer but this
	void startMusicLoop(Mix_Music* track);

	//Play the given Mix_Chunk exactly once
	//Delet this, no one should know about SDL Mixer but this
	void playSound(Mix_Chunk* sound);

	//Pause the music
	void pauseMusic();

	//Resume the music
	void resumeMusic();
}