
#include <iostream>

#include "Game.h"
#include "GlobalVariables.h"
#include "Player.h"

Player::Player(int initialHealth, int initialStrength, int initialSpeed, int initialPoints, int initialDollars)
{
	points	= initialPoints;
	dollars = initialDollars;

	alive = true;

	health	 = new Stat(initialHealth, "Health");
	strength = new Stat(initialStrength, "Strength");
	speed	 = new Stat(initialSpeed, "Speed");

	sizeX = 15;
	sizeY = 15;

	posX = Global::screenX / 2;
	posY = Global::screenY / 2;
	step = 1.5f;

	R = 1.0f;
	G = 1.0f;
	B = 1.0f;
}
Player::~Player()
{

}

void Player::addHealthPoint()
{
	addStat(health);
}
void Player::addStrengthPoint()
{
	addStat(strength);
}
void Player::addSpeedPoint()
{
	addStat(speed);
}

void Player::subtractHealthPoint()
{
	subtractStat(health);
}
void Player::subtractStrengthPoint()
{
	subtractStat(strength);
}
void Player::subtractSpeedPoint()
{
	subtractStat(speed);
}

void Player::addStat(Stat *stat_arg)
{
	switch(stat_arg->spentPoints)
	{
	case 0:
		if(points > 0)
		{
			points--;
			stat_arg->value++;
			stat_arg->spentPoints++;
		}
		break;
	case 1:
		if(points > 1)
		{
			points -= 2;
			stat_arg->value++;
			stat_arg->spentPoints++;
		}
		break;
	case 2:
		if(points > 3)
		{
			points -= 4;
			stat_arg->value++;
			stat_arg->spentPoints++;
		}
		break;
	}
}

void Player::subtractStat(Stat *stat_arg)
{
	switch(stat_arg->spentPoints)
	{
	case 1:
		points++;
		stat_arg->value--;
		stat_arg->spentPoints--;
		break;
	case 2:
		points += 2;
		stat_arg->value--;
		stat_arg->spentPoints--;
		break;
	case 3:
		points += 4;
		stat_arg->value--;
		stat_arg->spentPoints--;
		break;
	}
}

void Player::draw()
{
    glColor3f(R, G, B);

    glBegin(GL_QUADS);
		glVertex2f(posX,  posY);
		glVertex2f(posX + sizeX, posY);
		glVertex2f(posX + sizeX, posY + sizeY);
		glVertex2f(posX,  posY + sizeY);
	glEnd();
}
void Player::move(bool up, bool down, bool left, bool right)
{
	if(up)
		posY -= step;
	if(down)
		posY += step;
	if(left)
		posX -= step;
	if(right)
		posX += step;

	if(posX < 1)
		posX = 1;
	else
		if(posX > Global::screenX - sizeX)
			posX = Global::screenX - sizeX;

	if(posY < 1)
		posY = 1;
	else
		if(posY > Global::screenY - sizeY)
			posY = Global::screenY - sizeY;
}
void Player::checkCollitions(std::vector<Enemy*> *enemies)
{
	for(int i=0; i < enemies->size(); i++)
	{
		if((*enemies)[i]->alive)
		{
			if(	posX		 > (*enemies)[i]->posX && posX			< (*enemies)[i]->posX + (*enemies)[i]->sizeX &&
				posY		 > (*enemies)[i]->posY && posY			< (*enemies)[i]->posY + (*enemies)[i]->sizeY ||
				posX + sizeX > (*enemies)[i]->posX && posX + sizeX  < (*enemies)[i]->posX + (*enemies)[i]->sizeX &&
				posY		 > (*enemies)[i]->posY && posY			< (*enemies)[i]->posY + (*enemies)[i]->sizeY ||
				posX		 > (*enemies)[i]->posX && posX			< (*enemies)[i]->posX + (*enemies)[i]->sizeX &&
				posY + sizeY > (*enemies)[i]->posY && posY + sizeY  < (*enemies)[i]->posY + (*enemies)[i]->sizeY ||
				posX + sizeX > (*enemies)[i]->posX && posX + sizeX  < (*enemies)[i]->posX + (*enemies)[i]->sizeX &&
				posY + sizeY > (*enemies)[i]->posY && posY + sizeY  < (*enemies)[i]->posY + (*enemies)[i]->sizeY)
			{
				if(alive)
					fight((*enemies)[i]);
			}
		}
	}
}

void Player::fight(Enemy* enemy)
{
	if(enemy->speed > speed->value)
	{
		while(enemy->health > 0 && health->value > 0)
		{
			health->value -= enemy->strength;
			if(health->value > 0)
				enemy->health -= strength->value;
			else
				alive = false;
		}
		enemy->alive = false;
	}
	else
	{
		while(enemy->health > 0 && health->value > 0)
		{
			enemy->health -= strength->value;
			if(enemy->health > 0)
				health->value -= enemy->strength;
			else
				enemy->alive = false;
		}
		alive = false;
	}
}