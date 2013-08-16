#include <iostream>
#include <SDL.h>

#include "GlobalVariables.h"
#include "StateCredits.h"
#include "Game.h"

void closeCredits()
{
	Global::currentGame->setState(Global::currentGame->getMainMenuState());
}

StateCredits::StateCredits(void)
{

}
StateCredits::~StateCredits(void)
{

}

void StateCredits::loadBackground(std::string imageFile)
{ 	
	glGenTextures(1, &background);

	background = SOIL_load_OGL_texture(imageFile.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, NULL);

	glBindTexture(GL_TEXTURE_2D, background);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &backgroundSizeX);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &backgroundSizeY);
}
void StateCredits::init(Game &context)
{
	std::cout << "Initialising credits state." << std::endl;

	UI.addButton("Close (ESC) 1.png", "Close (ESC) 2.png", 6, Global::screenX / 2 - 70,  Global::screenY - 50, &closeCredits);
	
	SDL_Color colour = { 0, 230, 255 };

	// Adding labels to the text vector.
	text.push_back(new Label("Credits", Global::textFont, colour, Global::screenX / 2 - 50, 10, 1.5));
	text.push_back(new Label("Return of the Galactic Marine", Global::textFont, colour, Global::screenX / 2 - 190, 100, 1.2));
	text.push_back(new Label("Code written in C++", Global::textFont, colour, Global::screenX / 2 - 120, 200, 1.1));
	text.push_back(new Label("Using OpenGL, SDL,", Global::textFont, colour, Global::screenX / 2 - 120, 240, 1.1));
	text.push_back(new Label("SOIL and other libraries.", Global::textFont, colour, Global::screenX / 2 - 140, 280, 1.1));
	text.push_back(new Label("Author: Paulius Akulavicius (B00226642)", Global::textFont, colour, Global::screenX / 2 - 250, Global::screenY - 130, 1.1));

	loadBackground("background4.png");
}
void StateCredits::update(float deltaTime, unsigned int currentMS, Game &context)
{

}
void StateCredits::draw(SDL_Window * window)
{
	glClear(GL_COLOR_BUFFER_BIT);// | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

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

	for(int i=0; i<text.size(); i++)
	{
		text[i]->draw();
	}
	UI.draw();

	SDL_GL_SwapWindow(window);
}
void StateCredits::handleSDLEvent(SDL_Event const &sdlEvent, Game &context)
{
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
				closeCredits();
				break;
			case SDLK_ESCAPE:
				closeCredits();
			default:
				break;
		}
		break;

	default:
		break;
	}
}


