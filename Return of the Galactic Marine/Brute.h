#ifndef BRUTE_ENEMY
#define BRUTE_ENEMY

#include "Enemy.h"

class Brute: public Enemy
{
public:
	Brute(float positionX, float positionY);
	~Brute();
	void draw();
};

#endif