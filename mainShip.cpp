#include "stdafx.h"
#include "mainShip.h"


mainShip::mainShip()
{
}

mainShip::mainShip(int _x, int _y)
{
	x = _x;
	y = _y;
}


mainShip::~mainShip()
{
}

void mainShip::moveLeft() {
	x = x - 1;
}

void mainShip::moveRight() {
	x = x + 1;
}