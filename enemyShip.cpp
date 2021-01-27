#include "stdafx.h"

#include "enemyShip.h"


enemyShip::enemyShip()
{
}


enemyShip::~enemyShip()
{
}

enemyShip::enemyShip(int _x, int _y)
{
	x = _x;
	y = _y;
	shooted = false;
	missed = false;
}




void enemyShip::moveDown() {
	y = y + 1;
}

void enemyShip::destroyShip() {
	shooted = true;
}

bool enemyShip::isShooted() {
	return shooted;
}

void enemyShip::missedShip() {
	missed = true;
}

bool enemyShip::isMissed() {
	return missed;
}
