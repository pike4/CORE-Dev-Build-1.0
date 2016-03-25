#include "SDL.h"
#include "SDL_Image.h"
#include "Timer.h"
#include "VideoManager.h"
#include "_Manager.h"
#include <string>
#include <iostream>
#include <fstream>

#pragma once

using namespace std;

#pragma once

class SystemManager : Manager
{
public:
	static int state;

	static void start();

	static void update();

	static void updateFPS();

	static void stop();

	static void changeState(int state);

	static void flush();

	static void setoutputInterval(Uint32 ms);

	static bool hasElapsed(Uint32 ms);

	static void updateTime();
	static void printFPS();
	static void printObjectCount();
	static void drawableCount();


private:
	static Uint32 curTime;
	static Uint32 prevTime;
	static Uint32 outputInterval;

	static Uint32 totalTime;
	static Uint32 totalFrames;

	static Timer FPSTimer;

	static string buffer;

};