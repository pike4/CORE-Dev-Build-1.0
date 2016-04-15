#include "SDL.h"
#include "SDL_Mixer.h"
#include "SDL_TTF.h"
#include "SDL_Image.h"

#include "Thing.h"
#include "Updatable.h"
#include "ObjectManager.h"
#include "VideoManager.h"
#include "StateManager.h"
#include "AudioManager.h"
#include "AssetsManifest.h"
#include "TextObjects.h"
#include "BouncingBall.h"
#include "Spinner.h"
#include "Button.h"
#include "NavigationButton.h"
#include "SystemManager.h"
#include "pugixml.hpp"
#include "ResourceHashtable.h"
#include <map>

#undef main

SDL_Event e;

bool quit;

int main()
{
	StateManager::start();

	SDL_Texture* guy = SystemManager::loadTexture("Assets/Sprites/guy.png");
	SDL_Texture* real = SystemManager::loadTexture("Assets/Sprites/real.png");
	SDL_Texture* greg = SystemManager::loadTexture("Assets/Sprites/niceword.png");
	SDL_Texture* cage = SystemManager::loadTexture("Assets/Sprites/cage.png");
	SDL_Texture* peepee = SystemManager::loadTexture("Assets/Sprites/peepee.png");
	SDL_Texture* ball = SystemManager::loadTexture("Assets/Sprites/IMG_BouncingBall.png");

	SDL_Texture* hover = SystemManager::loadTexture("Assets/Sprites/BlankHover.png");
	SDL_Texture* held = SystemManager::loadTexture("Assets/Sprites/BlankHeld.png");
	SDL_Texture* def = SystemManager::loadTexture("Assets/Sprites/BlankDefault.png");
	
	Mix_Music* mega_Music = AudioManager::loadMusic("Assets/Music/a.ogg");
	TTF_Font* sans = TTF_OpenFont("Assets/Fonts/comic.ttf", 12);
	TTF_Font* bigSans = TTF_OpenFont("Assets/Fonts/comic.ttf", 50);
	pew = AudioManager::loadChunk("Assets/Music/pew.wav");
	//AudioManager::startMusicLoop(mega_Music);
	std::string curString = "a";
	pugi::xml_document doc;
	pugi::xml_parse_result  result = doc.load_file("g.xml");
	pugi::xml_node cur = doc.first_child();
	printf("AA    %s\n", cur.first_child().value());
	cur = doc.child("menu").child("button");
	GUI* fileLodedGUI = SystemManager::GUI_LoadFromFile(doc.child("menu"));


	SDL_Color color;
	color.a = 0;
	color.r = 0;
	color.g = 0;
	color.b = 255;

	SDL_Point point;
	point.x = 0;
	point.y = 0;
	
	/*ObjectManager::player = new Player(300, 200, 100, 100, greg);
	ObjectManager::add(new Thing(100, 100, guy));
	ObjectManager::add(new Thing(0, 0, real));
	ObjectManager::add(new Spinner(100, 100, peepee, 100.0));
	ObjectManager::add(new Spinner(350, 200, cage, 2.0));
	ObjectManager::add(new Spinner(400, 200, cage, -2.0));
	ObjectManager::add(new Spinner(200, 350, greg, 20.0));
	ObjectManager::add(new Spinner(400, 50, peepee, SDL_FLIP_NONE, 0, point, -10.0));*/

	for (int i = 0; i < 10; i++)
	{
		ObjectManager::add(new BouncingBall(100, 100, 8, 8, 0, 0, cage));
	}

	ObjectManager::add(new BouncingBall(100, 400, 8, 8, 0, -2, cage));

	SDL_Color d;
	d.r = 255;
	d.b = 0;
	d.g = 0;
	d.a = 255;

	Button a = Button(400, 300, def, hover, held, "WORD", sans, d,  pew);
	Button b = Button(400, 200, def, hover, held, "ANOTHER", sans, d,  pew);
	GUI gui2 = GUI();

	NavigationButton back = NavigationButton(400, 100, def, hover, held, "BACK", bigSans, d, pew, ObjectManager::currentGUI);

	Button c = Button(400, 200, def, hover, held, "WELL", bigSans, d, pew);
	Button e = Button(400, 300, def, hover, held, "OK THEN", sans, d, pew);

	NavigationButton start = NavigationButton(400, 100, def, hover, held, "START", sans, d, pew, &gui2);
	
	gui2.add(&c);
	gui2.add(&e);
	gui2.add(&back);

	std::vector<Button*> bb;
	ObjectManager::add(&a);
	ObjectManager::add(&b);
	bb.push_back(&a);
	Button* array[3] = { &a, &b};
	ObjectManager::currentGUI->add(array, 2);
	ObjectManager::currentGUI = fileLodedGUI;
	VideoManager::currentGUI = ObjectManager::currentGUI;

	for (int i = 0; i < 20; i++)
	{
		ObjectManager::add(new BouncingBall(400, 20 + (10 * i), 8, 8, -i, 1, cage));
	}

	//ObjectManager::add(new BouncingBall(100, 100, 8, 8, 100, 0, ball));
	//ObjectManager::add(new BouncingBall(300, 100, 8, 8, 10, 0, ball));
	/*ObjectManager::add(new BouncingBall(300, 100, 8, 8, -10, 10, ball));
	ObjectManager::add(new BouncingBall(300, 300, 8, 8, -10, -10, ball));*/
	//ObjectManager::add(new BouncingBall(200, 200, 8, 8, 5, 10, ball));

	ObjectManager::add(new PlainText(0, 0, sans, "I will build a great wall and nobody builds walls better than me, believe me and I\'ll build them very inexpensively.", color));
	ObjectManager::add(new PlainText(0, 30, sans, "I will build a great, great wall on our southern border, and I will make Mexico pay for that wall. Mark my words.", color));

	while (!quit)
	{
		StateManager::update();
	}

	return 0;
}