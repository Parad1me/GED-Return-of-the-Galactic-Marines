#ifndef ENEMY_CLASS
#define ENEMY_CLASS

class Enemy
{
protected:
	
	float R, G, B;
public:
	virtual ~Enemy() { return; }
	virtual void draw() = 0;

	float posX, posY, sizeX, sizeY;
	int health, strength, speed, moneyDrop, itemDrop;
	bool alive;
};

#endif