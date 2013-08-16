#include <iostream>

#include "StateIntro.h"
#include "Game.h"

#include <SDL.h>

StateIntro::StateIntro(void)
{
}
StateIntro::~StateIntro(void)
{
}

void StateIntro::loadImage()
{
	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &texture);

	texture = SOIL_load_OGL_texture("intro.bmp", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, NULL);

	glBindTexture(GL_TEXTURE_2D, texture);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &backgroundSizeX);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &backgroundSizeY);

	glDisable(GL_TEXTURE_2D);
}
void StateIntro::init(Game &context)
{
	std::cout << "Initialising intro state." << std::endl;
	loadImage();
	introTime = 2000;
	startTime = 0;
}
void StateIntro::update(float deltaTime, unsigned int currentMS, Game &context)
{
	if(startTime == 0)
		startTime = currentMS;
	if(currentMS - startTime >= introTime)
	{
		context.setState(context.getMainMenuState());
	}
}
void StateIntro::draw(SDL_Window * window)
{
	glClear(GL_COLOR_BUFFER_BIT);// | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

	glColor3f(1.0f, 1.0f, 1.0f);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex2f(1.0f,1.0f);
		glTexCoord2f(1,0); glVertex2f(1.0f + backgroundSizeX, 1.0f);
		glTexCoord2f(1,1); glVertex2f(1.0f + backgroundSizeX, 1.0f + backgroundSizeY);
		glTexCoord2f(0,1); glVertex2f(1.0f, 1.0f + backgroundSizeY);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	SDL_GL_SwapWindow(window);
}
void StateIntro::handleSDLEvent(SDL_Event const &sdlEvent, Game &context)
{
	if (sdlEvent.type == SDL_KEYDOWN)
	{
		//std::cout << "Scancode: " << sdlEvent.key.keysym.scancode ;
        //std::cout << ", Name: " << SDL_GetKeyName( sdlEvent.key.keysym.sym ) << std::endl;
		switch( sdlEvent.key.keysym.sym )
		{
			case SDLK_RETURN:
			case SDLK_RETURN2:
				context.setState(context.getMainMenuState());
				break;
			case SDLK_ESCAPE:
				// Create a SDL quit event and push into the event queue
				//SDL_Event quitEvent;
				//quitEvent.type = SDL_QUIT;
				//SDL_PushEvent(&quitEvent);
			default:
				break;
		}
	}
}


