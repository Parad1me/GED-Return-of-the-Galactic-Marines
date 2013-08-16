#ifndef STATE_CHAR_CUSTOMIZATION
#define STATE_CHAR_CUSTOMIZATION

#include <iostream>
#include <string>
#include <vector>

#include "Buttons.h"
#include "Label.h"
#include "gameState.h"

class StateCharCustom : public GameState
{
public:
	StateCharCustom(void);
	~StateCharCustom(void);
	void init(Game &context);
	void loadBackground(std::string imageFile);
	void update(float deltaTime, unsigned int currentMS, Game &context);
	void draw(SDL_Window * window);
	void handleSDLEvent(SDL_Event const &sdlEvent, Game &context);

private:
	int backgroundSizeX, backgroundSizeY;
	GLuint background;
	Interface UI;
	Label *health, *speed, *strength, *points;
	std::vector<Label*> text;
	SDL_Color colour;
};

#endif