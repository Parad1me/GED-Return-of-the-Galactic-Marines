
#include "Game.h"
#include "Raider.h"

Raider::Raider(float positionX, float positionY)
{
	posX = positionX;
	posY = positionY;
	sizeX = 20.0f;
	sizeY = 20.0f;

	R = 1.0f;
	G = 0.0f;
	B = 0.0f;

	health = 12;
	strength = 7;
	speed = 12;
	moneyDrop = 100;
	itemDrop = 40;

	alive = true;
}
Raider::~Raider()
{

}
void Raider::draw()
{
	if(alive)
	{
		glColor3f(R, G, B);
		
		glBegin(GL_QUADS);
			glVertex2f(posX,  posY);
			glVertex2f(posX + sizeX, posY);
			glVertex2f(posX + sizeX, posY + sizeY);
			glVertex2f(posX,  posY + sizeY);
		glEnd();
	}
}