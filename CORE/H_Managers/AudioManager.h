#include "SDL.h"
#include "SDL_Mixer.h"
#include "Commands.h"
#include "_Manager.h"
#include <string>

#pragma once

class AudioManager : public Manager
{
public:

	static int state;

	static bool start();

	static void update();

	static void updateRunning();
	static void updateInMenu();
	static void updatePaused();
	static void updateBlocking();

	static void goToState(int);

	static void goToBlocking();
	static void goToPaused();
	static void goToRunning();
	static void goToInMenu();

	static void handleEvent(int eventCode, int posOrNeg = 0, int x = 0, int y = 0);

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

