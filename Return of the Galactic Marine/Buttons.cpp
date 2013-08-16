//#include <string>

#include "Buttons.h"

#include <iostream>

Interface::Interface()
{
	std::cout << "Creating GUI." << std::endl;
}
Interface::~Interface()
{

}

void Interface::addButton(std::string imageA, std::string imageB, int scancode_arg, int positionX, int positionY, void (*callback)())
{
	buttons.push_back(new Interface::Button(imageA, imageB, scancode_arg, positionX, positionY, callback));
}
void Interface::addButton(std::string imageA, std::string imageB, int scancode_arg, int positionX, int positionY, void (*callback)(), int positionIndex)
{
	delete buttons[positionIndex];
	buttons[positionIndex] = new Interface::Button(imageA, imageB, scancode_arg, positionX, positionY, callback);
}
void Interface::mouseMovement(int x, int y)
{
	for(int i=0; i < buttons.size(); i++)
	{
		if(	x > buttons[i]->positionX && x < buttons[i]->positionX + buttons[i]->sizeX && 
			y > buttons[i]->positionY && y < buttons[i]->positionY + buttons[i]->sizeY)
			buttons[i]->currentImage = buttons[i]->imageB;
		else
			buttons[i]->currentImage = buttons[i]->imageA;
	}
}
void Interface::mouseClick(int x, int y)
{
	for(int i=0; i < buttons.size(); i++)
	{
		if(	x > buttons[i]->positionX && x < buttons[i]->positionX + buttons[i]->sizeX && 
			y > buttons[i]->positionY && y < buttons[i]->positionY + buttons[i]->sizeY)
			buttons[i]->callback();
	}
}
void Interface::keypress(SDL_Scancode scancode_arg)
{
	for(int i=0; i < buttons.size(); i++)
	{
		if(scancode_arg == buttons[i]->scancode)
			buttons[i]->callback();
	}
}
int Interface::getLastButtonIndex()
{
	return buttons.size() - 1;
}

void Interface::draw()
{
	glEnable(GL_TEXTURE_2D);

	for(int i=0; i < buttons.size(); i++)
	{
		glColor3f(0.80f, 0.80f, 0.80f);
		glBindTexture(GL_TEXTURE_2D, buttons[i]->currentImage);
		glBegin(GL_QUADS);
			glTexCoord2f(0,0); glVertex2f(buttons[i]->positionX,  buttons[i]->positionY);
			glTexCoord2f(1,0); glVertex2f(buttons[i]->positionX + buttons[i]->sizeX, buttons[i]->positionY);
			glTexCoord2f(1,1); glVertex2f(buttons[i]->positionX + buttons[i]->sizeX, buttons[i]->positionY + buttons[i]->sizeY);
			glTexCoord2f(0,1); glVertex2f(buttons[i]->positionX,  buttons[i]->positionY + buttons[i]->sizeY);
		glEnd();

	}

	glDisable(GL_TEXTURE_2D);
}