#ifndef PLAYER_CLASS
#define PLAYER_CLASS

#include <string>
#include <vector>

#include "Enemy.h"

class Player
{
public:
	
	struct Stat
	{
		Stat(int initialValue, std::string statName)
		{
			value = initialValue;
			name = statName;
			spentPoints = 0;
		}

		int value, spentPoints;
		std::string name;
	};

	Player(int initialHealth, int initialStrength, int initialSpeed, int initialPoints, int initialDollars);
	~Player();

	void addHealthPoint();
	void addStrengthPoint();
	void addSpeedPoint();
	
	void subtractHealthPoint();
	void subtractStrengthPoint();
	void subtractSpeedPoint();

	void addStat(Stat *stat_arg);
	void subtractStat(Stat *stat_arg);

	void draw();
	void move(bool up, bool down, bool left, bool right);

	void checkCollitions(std::vector<Enemy*> *enemies);

	int dollars, points;
	Stat *health, *strength, *speed;

	bool alive;

private:
	void fight(Enemy* enemy);
	float posX, posY, sizeX, sizeY, step, R, G, B;
};

#endif