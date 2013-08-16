#ifndef STATE_INTRO
#define STATE_INTRO

#include "GameState.h"
#include "Label.h"

class StateIntro : public GameState
{
public:
	StateIntro(void);
	~StateIntro(void);
	void init(Game &context);
	void draw(SDL_Window * window);
	void update(float deltaTime, unsigned int currentMS, Game &context);
	void handleSDLEvent(SDL_Event const &sdlEvent, Game &context);
private:
	void loadImage(void);
	GLuint texture, txtest;
	SDL_Surface *image, *image2;
	float introTime, startTime;
	int backgroundSizeX, backgroundSizeY;
};

#endif