#ifndef STATE_PLAY
#define STATE_PLAY

#include <cstdlib>
#include <ctime>
#include <vector>

#include "Enemy.h"
#include "Label.h"
#include "gameState.h"
#include "Brute.h"
#include "Fodder.h"
#include "Raider.h"

class StatePlay : public GameState
{
public:
	StatePlay(void);
	~StatePlay(void);
	void init(Game &context);
	void loadBackground(std::string imageFile);
	void update(float deltaTime, unsigned int currentMS, Game &context);
	void draw(SDL_Window * window);
	void handleSDLEvent(SDL_Event const &sdlEvent, Game &context);
private:

	clock_t lastTime; // clock_t is an integer type
	clock_t currentTime; // use this to track time between frames
	
	bool keyUp, keyDown, keyRight, keyLeft, gameOver, gameOverTimer;
	int backgroundSizeX, backgroundSizeY, numOfRaiders, numOfBrutes, numOfFodders;
	GLuint background;

	Raider *raiderNPC;
	std::vector<Enemy*> enemies;
	std::string enemyFileName;
	
	Label *health, *speed, *strength, *money;
	std::vector<Label*> text;
	SDL_Color colour;
};

#endif