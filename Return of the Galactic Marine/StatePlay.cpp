#include "StatePlay.h"
#include <iostream>
// stringstream and string
#include <sstream>
#include <string>
#include <fstream>

// While a declaration of class Game has been provided in
// gamestate.h, this was only a forward declaration
// because we need to work with the implementation now
// we need to include game.h here
#include "Game.h"
#include "GlobalVariables.h"
#include "toString.h"

using namespace ToString;

StatePlay::StatePlay(void)
{

}


StatePlay::~StatePlay(void)
{

}

void StatePlay::init(Game &context)
{
	std::cout << "Initialising play state." << std::endl;
	
	loadBackground("background5.png");
	enemyFileName = "enemies.txt";
	gameOver = false;
	gameOverTimer = false;

	SDL_Color colour = { 255, 255, 255 };

	text.push_back(new Label("Health :",	Global::textFont, colour, 10,  0, 1));
	text.push_back(new Label("Speed :",		Global::textFont, colour, 10, 20, 1));
	text.push_back(new Label("Strength :",	Global::textFont, colour, 10, 40, 1));
	text.push_back(new Label("Money :",		Global::textFont, colour, 10, 60, 1));
	
	text.push_back(new Label("Press ESC to quit/pause",	Global::textFont, colour, Global::screenX - 280, 0, 1));
	
	text.push_back(new Label("0",	Global::textFont, colour, 120,  0, 1)); health	 = text[text.size() - 1];
	text.push_back(new Label("0",	Global::textFont, colour, 120, 20, 1)); speed	 = text[text.size() - 1];
	text.push_back(new Label("0",	Global::textFont, colour, 120, 40, 1)); strength = text[text.size() - 1];
	text.push_back(new Label("0",	Global::textFont, colour, 120, 60, 1)); money	 = text[text.size() - 1];

	keyUp = false;
	keyDown = false;
	keyLeft = false;
	keyRight = false;
	
	std::fstream enemyFile;
	std::string singleWord;
	enemyFile.open(enemyFileName, std::ios::in);

	if(enemyFile.fail())
	{
		std::cout << "Failed to open the enemy file" << endl;
	}

	enemyFile >> singleWord;
	numOfRaiders = std::atoi(singleWord.c_str());
	enemyFile >> singleWord;
	numOfBrutes = std::atoi(singleWord.c_str());
	enemyFile >> singleWord;
	numOfFodders = std::atoi(singleWord.c_str());

	enemyFile.close();

	for(int i=0; i<numOfRaiders; i++)
		enemies.push_back(new Raider(rand() % Global::screenX + 1, rand() % Global::screenY + 50));
	for(int i=0; i<numOfRaiders; i++)
		enemies.push_back(new Brute(rand() % Global::screenX + 1, rand() % Global::screenY + 50));
	for(int i=0; i<numOfRaiders; i++)
		enemies.push_back(new Fodder(rand() % Global::screenX + 1, rand() % Global::screenY + 50));
}
void StatePlay::loadBackground(std::string imageFile)
{ 	
	glGenTextures(1, &background);

	background = SOIL_load_OGL_texture(imageFile.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, NULL);

	glBindTexture(GL_TEXTURE_2D, background);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &backgroundSizeX);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &backgroundSizeY);
}

void StatePlay::update(float deltaTime, unsigned int currentMS, Game &context)
{
	if(!gameOver)
	{
		Global::currentPlayer->move(keyUp, keyDown, keyLeft, keyRight);
		Global::currentPlayer->checkCollitions(&enemies);

		health->setText(toString(Global::currentPlayer->health->value).c_str(), Global::textFont);
		speed->setText(toString(Global::currentPlayer->speed->value).c_str(), Global::textFont);
		strength->setText(toString(Global::currentPlayer->strength->value).c_str(), Global::textFont);
		money->setText(toString(Global::currentPlayer->dollars).c_str(), Global::textFont);
	}
	else
	{
		if(!gameOverTimer)
		{
			gameOverTimer = true;
			
			std::clock_t now = std::clock();
			std::clock_t end;
			end = now + 2 * CLOCKS_PER_SEC;
			while (now < end )
				now = std::clock();

			Global::currentGame->setState(Global::currentGame->getCreditsState());
		}
	}

	if(!Global::currentPlayer->alive && !gameOver)
	{
		gameOver = true;
		SDL_Color tempColour = { 255, 0, 0 };
		text.push_back(new Label("GAME OVER", Global::textFont, tempColour, Global::screenX / 2 - 220,  Global::screenY / 2, 3));
	}
}

// The main rendering function
// In principle, this function should never perform updates to the game
// ONLY render the current state. Reacting to events should be taken care
// of in a seperate update function
void StatePlay::draw(SDL_Window * window)
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

	for(int i=0; i<enemies.size(); i++)
		enemies[i]->draw();
	
	for(int i=0; i<text.size(); i++)
		text[i]->draw();

	Global::currentPlayer->draw();

	SDL_GL_SwapWindow(window);
}


// The event handling function
// In principle, this function should never perform updates to the game
// ONLY detect what events have taken place. Reacting to the events should
// be taken care of in a seperate update function
// This would allow e.g. diagonal movement when two keys are pressed together
// (which is not possible with this implementation)
void StatePlay::handleSDLEvent(SDL_Event const &sdlEvent, Game &context)
{
	switch(sdlEvent.type)
	{
	case SDL_MOUSEMOTION:

		break;

	case SDL_MOUSEBUTTONUP:

		break;

	case SDL_KEYDOWN:

		switch(sdlEvent.key.keysym.sym)
		{
		case SDLK_UP:
			keyUp = true; 
			break;
		case SDLK_DOWN:
			keyDown = true; 
			break;
		case SDLK_RIGHT:
			keyRight = true;
			break;
		case SDLK_LEFT:
			keyLeft = true;
		break;

		case SDLK_RETURN:
		case SDLK_RETURN2:
			//context.setState(context.getPlayState());
			break;
		case SDLK_ESCAPE:
			Global::currentGame->setState(Global::currentGame->getMainMenuState());
			break;
		default:
			break;
		}
		break;

	case SDL_KEYUP:

		switch(sdlEvent.key.keysym.sym)
		{
		case SDLK_UP:
			keyUp = false; 
			break;
		case SDLK_DOWN:
			keyDown = false; 
			break;
		case SDLK_RIGHT:
			keyRight = false;
			break;
		case SDLK_LEFT:
			keyLeft = false;
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}

}
