#pragma once
#include "ship.h"
class enemyShip: public ship
{

private:
	bool shooted;
	bool missed;
public:
	enemyShip();
	~enemyShip();
	enemyShip(int, int);
	void destroyShip();
	bool isShooted();
	void missedShip();
	bool isMissed();
	void moveDown();

};

