#ifndef FODDER_ENEMY
#define FODDER_ENEMY

#include "Enemy.h"

class Fodder: public Enemy
{
public:
	Fodder(float positionX, float positionY);
	~Fodder();
	void draw();
};

#endif