#pragma once
#include "ship.h"
class mainShip :
	public ship
{
public:
	mainShip();
	mainShip(int, int);
	~mainShip();
	void moveLeft();
	void moveRight();
};

