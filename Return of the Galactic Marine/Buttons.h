#ifndef BUTTONS
#define BUTTONS

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>

#include "Game.h"

class Interface
{
public:

	Interface();
	~Interface();

	void addButton(std::string imageA, std::string imageB, int scancode_arg, int positionX, int positionY, void (*callback)());
	void addButton(std::string imageA, std::string imageB, int scancode_arg, int positionX, int positionY, void (*callback)(), int positionIndex);
	void mouseMovement(int x, int y);
	void mouseClick(int x, int y);
	void keypress(SDL_Scancode scancode_arg);
	int getLastButtonIndex();

	void draw();

	void (*func)();

private:

	struct Button
	{
		Button(std::string imageA_arg, std::string imageB_arg, int scancode_arg, int positionX_arg, int positionY_arg, void (*callback_arg)())
		{
			positionX = positionX_arg;
			positionY = positionY_arg;
			callback = callback_arg;
			scancode = SDL_Scancode(scancode_arg);

			loadImages(imageA_arg, imageB_arg);
		}

		void loadImages(std::string imageA_arg, std::string imageB_arg)
		{			
			glGenTextures(1, &imageA);
			glGenTextures(1, &imageB);

			imageA = SOIL_load_OGL_texture(imageA_arg.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_MULTIPLY_ALPHA);
			imageB = SOIL_load_OGL_texture(imageB_arg.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_MULTIPLY_ALPHA);

			currentImage = imageA;

			glBindTexture(GL_TEXTURE_2D, imageA);
			glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &sizeX);
			glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &sizeY);
		}

		int positionX, positionY;
		int sizeX, sizeY;
		void (*callback)();
		GLuint imageA, imageB, currentImage;
		SDL_Scancode scancode;
	};

	std::vector<Button*> buttons;

};

#endif