#include "StateMainMenu.h"
#include <iostream>

// While a declaration of class Game has been provided in
// gamestate.h, this was only a forward declaration
// because we need to work with the implementation now
// we need to include game.h here
#include "Game.h"
#include "GlobalVariables.h"

void setCharCustomState()
{
	Global::currentGame->setState(Global::currentGame->getCharCustom());
	Global::newGameStarted = true;
}
void setCreditsState()
{
	Global::currentGame->setState(Global::currentGame->getCreditsState());
}
void continueToPlayState()
{
	Global::currentGame->setState(Global::currentGame->getPlayState());
}

void quitGame()
{
	Global::currentGame->quit();
}

StateMainMenu::StateMainMenu(void)
{

}
StateMainMenu::~StateMainMenu(void)
{

}

void StateMainMenu::loadBackground(std::string imageFile)
{ 	
	glGenTextures(1, &background);

	background = SOIL_load_OGL_texture(imageFile.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, NULL);

	glBindTexture(GL_TEXTURE_2D, background);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &backgroundSizeX);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &backgroundSizeY);
}
void StateMainMenu::init(Game &context)
{
	std::cout << "Initialising main menu state." << std::endl;

	loadBackground("background3.png");

	UI.addButton("New Game (N) 1.png", "New Game (N) 2.png", 17, 10, Global::screenY - 120, &setCharCustomState);
	newGameButtonIndex = UI.getLastButtonIndex();
	UI.addButton("Credits (R) 1.png", "Credits (R) 2.png", 21, 10, Global::screenY - 80, &setCreditsState);
	UI.addButton("Quit (Q-ESC) 1.png", "Quit (Q-ESC) 2.png", 20, 10, Global::screenY - 40, &quitGame);

	newGameButtonUpdated = false;
}
void StateMainMenu::update(float deltaTime, unsigned int currentMS, Game &context)
{
	if(!newGameButtonUpdated && Global::newGameStarted)
	{
		UI.addButton("Continue (C) 1.png", "Continue (C) 2.png", 6, 10, Global::screenY - 120, &continueToPlayState, newGameButtonIndex);
		newGameButtonUpdated = true;
	}
}
void StateMainMenu::draw(SDL_Window * window)
{
	glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f);
	
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, background);
    glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex2f(1.0f, 1.0f);
		glTexCoord2f(1,0); glVertex2f(1.0f + backgroundSizeX, 1.0f);
		glTexCoord2f(1,1); glVertex2f(1.0f + backgroundSizeX, 1.0f + backgroundSizeY);
		glTexCoord2f(0,1); glVertex2f(1.0f, 1.0f + backgroundSizeY);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	UI.draw();

	SDL_GL_SwapWindow(window);
}
void StateMainMenu::handleSDLEvent(SDL_Event const &sdlEvent, Game &context)
{
	//std::cout << "Event handling in main menu state." << std::endl;

	switch(sdlEvent.type)
	{
	case SDL_MOUSEMOTION:
		UI.mouseMovement(sdlEvent.motion.x, sdlEvent.motion.y);
		break;

	case SDL_MOUSEBUTTONUP:
		UI.mouseClick(sdlEvent.motion.x, sdlEvent.motion.y);
		break;

	case SDL_KEYDOWN:

		UI.keypress(sdlEvent.key.keysym.scancode);

		switch( sdlEvent.key.keysym.sym )
		{
			case SDLK_RETURN:
			case SDLK_RETURN2:
				//context.setState(context.getPlayState());
				break;
			case SDLK_ESCAPE:
				Global::currentGame->quit();
			default:
				break;
		}
		break;

	default:
		break;
	}
}


