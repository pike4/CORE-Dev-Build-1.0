#pragma once

#include "SDL.h"
#include "SDL_Mixer.h"

#include <string>


/*
   CORE Audio subsystem
   Purpose:
      1. Abstract 3rd party audio APIs away from the rest of the engine
      2. Expose a public API for:
         a. Loading and freeing audio files by name
         b. Managing audio playback channels
         c. Playing, pausing, and stopping tracks by name on a specified channels
         d. Advanced playback options for tracks such as fade-in/out, looping certain
            portions of a track, reverb, and positional audio
         e. Setting channel attributes such as relative volume
*/

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
	//startLoop(string track, string channel);

   //TODO: Loop the given sound on the given channel, looping back to the given point in time at the 
   //loop's end
   //startLoop(string track, string channel, double restartTime);

   //TODO: Loop the given sound, looping back to restartTime when endTime is reached
   //startLoop(string track, string channel, double startTime, double endTime);

	//TODO: set the volume for the specified track
	//setVolume(string channel, double volume);

   //TODO: set the master volume and limit all tracks to the given volume
   //setVolume(double volume);

	//TODO: play the given sound on the given track
	//playSound(string track, string channel);

	void update();

	void handleEvent(int eventCode, int posOrNeg = 0, int x = 0, int y = 0);


	//These two belong to CORE_Resources
   //No it doesn't
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