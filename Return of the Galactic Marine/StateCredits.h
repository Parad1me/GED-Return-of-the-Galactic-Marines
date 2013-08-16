#ifndef STATE_CREDITS
#define STATE_CREDITS

#include "Buttons.h"
#include "GameState.h"
#include "Label.h"

class StateCredits : public GameState
{
public:
	StateCredits(void);
	~StateCredits(void);
	void init(Game &context);
	void draw(SDL_Window * window);
	void update(float deltaTime, unsigned int currentMS, Game &context);
	void handleSDLEvent(SDL_Event const &sdlEvent, Game &context);
private:
	void loadBackground(std::string imageFile);
	int backgroundSizeX, backgroundSizeY;
	GLuint background;
	Interface UI;
	std::vector<Label*> text;
	SDL_Color colour;
};

#endif