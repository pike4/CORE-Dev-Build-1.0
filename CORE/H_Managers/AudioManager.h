#include "SDL.h"
#include "SDL_Mixer.h"
#include "Commands.h"
#include "_Manager.h"
#include <string>

#pragma once

class AudioManager : public Manager
{
public:

	static bool start();

	static void update();

	static Mix_Music* loadMusic(char* filename);

	static Mix_Chunk* loadChunk(char* filename);

	//Begin a continuous loop of the given Mix_Music. 
	static void startMusicLoop(Mix_Music* track);

	//Play the given Mix_Chunk exactly once
	static void playSound(Mix_Chunk* sound);

	//Pause the music
	static void pauseMusic();

	//Resume the music
	static void resumeMusic();

};
