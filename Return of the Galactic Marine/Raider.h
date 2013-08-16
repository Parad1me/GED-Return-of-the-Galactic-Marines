#ifndef RAIDER_ENEMY
#define RAIDER_ENEMY

#include "Enemy.h"

class Raider: public Enemy
{
public:
	Raider(float positionX, float positionY);
	~Raider();
	void draw();
};

#endif