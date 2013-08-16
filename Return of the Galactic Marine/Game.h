#ifndef GAME_MAIN
#define GAME_MAIN

#include <iostream>
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_ttf.h>

// C stdlib and C time libraries for rand and time functions
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <SOIL.h>
#include <stdlib.h>
#include <time.h> 

#include "GameState.h"
#include "label.h"
#include "Player.h"

#include "Timer.h"

class Game {
public:
	// Constructor and destructor methods
	Game(void);
	~Game();
	// init and run are the only functions that need called from main
	void init(void);
	void run(void);
	void quit(void);
	void globalUpdate(void);
	void setState(GameState * newState);
	GameState *getState(void);
	GameState *getPlayState(void);
	GameState *getIntroState(void);
	GameState *getMainMenuState(void);
	GameState *getCharCustom(void);
	GameState *getCreditsState(void);

	Player *player;
	
private:
	
	// The game states:
	GameState * playState;
	GameState * introState;
	GameState * mainMenuState;
	GameState * currentState;
	GameState * charCustom;
	GameState * creditsState;

	// setupRC will be called when game is created
	void setupRC(void);
	// The game loop will call update, draw and handle event methods provided by each state

	SDL_Window *window;
	// This needs changed... currently I refer to the Game object as the context for the different
	// states, so should use a specific (and diff) name to refer to the gl context
	// to avoid confusion
	SDL_GLContext context;

	static int instances;

	clock_t lastTime; // clock_t is an integer type
	clock_t currentTime; // use this to track time between frames
	
	timer *Timer;
	string windowTitle;
	float deltaTime;
};

#endif