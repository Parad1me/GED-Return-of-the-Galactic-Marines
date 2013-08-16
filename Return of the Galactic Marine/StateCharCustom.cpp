#include "Game.h"
#include "GlobalVariables.h"
#include "StateCharCustom.h"
#include "toString.h"

using namespace ToString;

// These functions aren't a part of class methods.
// They are made this way, so it is possible to pass them as function pointers.
void setMainMenuState()
{
	Global::currentGame->setState(Global::currentGame->getMainMenuState());
}
void setPlayState()
{
	Global::currentGame->setState(Global::currentGame->getPlayState());
}

void addHealthPoint()
{
	Global::currentPlayer->addHealthPoint();
}
void addSpeedPoint()
{
	Global::currentPlayer->addSpeedPoint();
}
void addStrengthPoint()
{
	Global::currentPlayer->addStrengthPoint();
}

void subtractHealthPoint()
{
	Global::currentPlayer->subtractHealthPoint();
}
void subtractSpeedPoint()
{
	Global::currentPlayer->subtractSpeedPoint();
}
void subtractStrengthPoint()
{
	Global::currentPlayer->subtractStrengthPoint();
}

StateCharCustom::StateCharCustom()
{

}
StateCharCustom::~StateCharCustom()
{

}

void StateCharCustom::init(Game &context)
{
	std::cout << "Initialising character customomization state." << std::endl;
	
	// Passing 512 as SCANCODE, so it won't be triggered by pressing a button. 512 doesn't exsist as a button.
	UI.addButton("+ 1.png", "+ 2.png", 512, Global::screenX / 2 + 70,  Global::screenY / 2 - 120, &addHealthPoint);
	UI.addButton("- 1.png", "- 2.png", 512, Global::screenX / 2 - 145, Global::screenY / 2 - 120, &subtractHealthPoint);
	
	UI.addButton("+ 1.png", "+ 2.png", 512, Global::screenX / 2 + 70,  Global::screenY / 2 - 80, &addSpeedPoint);
	UI.addButton("- 1.png", "- 2.png", 512, Global::screenX / 2 - 145, Global::screenY / 2 - 80, &subtractSpeedPoint);
	
	UI.addButton("+ 1.png", "+ 2.png", 512, Global::screenX / 2 + 70,  Global::screenY / 2 - 40, &addStrengthPoint);
	UI.addButton("- 1.png", "- 2.png", 512, Global::screenX / 2 - 145, Global::screenY / 2 - 40, &subtractStrengthPoint);

	UI.addButton("Continue (C) 1.png", "Continue (C) 2.png", 6, Global::screenX - 170,  Global::screenY - 50, &setPlayState);
	
	SDL_Color colour = { 0, 147, 170 };

	// Adding labels to the text vector.
	text.push_back(new Label("Character Customization", Global::textFont, colour, Global::screenX / 2 - 190, 10, 1.5));
	text.push_back(new Label("Health:", Global::textFont, colour, Global::screenX / 2 - 80, Global::screenY / 2 - 120, 1));
	text.push_back(new Label("Speed:", Global::textFont, colour, Global::screenX / 2 - 80, Global::screenY / 2 - 80, 1));
	text.push_back(new Label("Strength:", Global::textFont, colour, Global::screenX / 2 - 80, Global::screenY / 2 - 40, 1));
	text.push_back(new Label("Points left:", Global::textFont, colour, Global::screenX / 2 - 100, Global::screenY / 2 + 40, 1));
	
	text.push_back(new Label(toString(0).c_str(), Global::textFont, colour, Global::screenX / 2 + 30, Global::screenY / 2 - 120, 1));
	health	 = text[text.size() - 1];		// Assigning label to a pointer, so it could be updated later.
	text.push_back(new Label(toString(0).c_str(), Global::textFont, colour, Global::screenX / 2 + 30, Global::screenY / 2 - 80, 1));
	speed	 = text[text.size() - 1];
	text.push_back(new Label(toString(0).c_str(), Global::textFont, colour, Global::screenX / 2 + 30, Global::screenY / 2 - 40, 1));
	strength = text[text.size() - 1];
	text.push_back(new Label(toString(0).c_str(), Global::textFont, colour, Global::screenX / 2 + 30, Global::screenY / 2 + 40, 1));
	points	 = text[text.size() - 1];
	
	loadBackground("background2.png");
}
void StateCharCustom::loadBackground(std::string imageFile)
{ 	
	glGenTextures(1, &background);

	background = SOIL_load_OGL_texture(imageFile.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, NULL);

	glBindTexture(GL_TEXTURE_2D, background);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &backgroundSizeX);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &backgroundSizeY);
}
void StateCharCustom::update(float deltaTime, unsigned int currentMS, Game &context)
{
	// Updating the text of labels with variable value.
	health->setText(toString(Global::currentPlayer->health->value).c_str(), Global::textFont);
	speed->setText(toString(Global::currentPlayer->speed->value).c_str(), Global::textFont);
	strength->setText(toString(Global::currentPlayer->strength->value).c_str(), Global::textFont);
	points->setText(toString(Global::currentPlayer->points).c_str(), Global::textFont);
}
void StateCharCustom::draw(SDL_Window * window)
{
	glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f);
	
	// Drawing the background picture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, background);
    glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex2f(1.0f, 1.0f);
		glTexCoord2f(1,0); glVertex2f(1.0f + backgroundSizeX, 1.0f);
		glTexCoord2f(1,1); glVertex2f(1.0f + backgroundSizeX, 1.0f + backgroundSizeY);
		glTexCoord2f(0,1); glVertex2f(1.0f, 1.0f + backgroundSizeY);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// Drawing labels from the 'text' vector.
	for(int i=0; i < text.size(); i++)
	{
		text[i]->draw();
	}
	// Calling draw method in UI class to draw all the buttons
	UI.draw();

	SDL_GL_SwapWindow(window);
}
void StateCharCustom::handleSDLEvent(SDL_Event const &sdlEvent, Game &context)
{
	//std::cout << "Event handling in main menu state." << std::endl;

	switch(sdlEvent.type)
	{
	case SDL_MOUSEMOTION:
		UI.mouseMovement(sdlEvent.motion.x, sdlEvent.motion.y); // Passing mouse movements to UI class, to detect when the mouse is over the buttons.
		break;

	case SDL_MOUSEBUTTONUP:
		UI.mouseClick(sdlEvent.motion.x, sdlEvent.motion.y);
		break;

	case SDL_KEYDOWN:

		UI.keypress(sdlEvent.key.keysym.scancode); // Passing key presses to UI class, so that buttons with assigned SCANCODE can be activated via keyboard.

		switch( sdlEvent.key.keysym.sym )
		{
			case SDLK_RETURN:
			case SDLK_RETURN2:
				//context.setState(context.getPlayState());
				break;
			case SDLK_ESCAPE:
				setMainMenuState();
			default:
				break;
		}
		break;

	default:
		break;
	}
}