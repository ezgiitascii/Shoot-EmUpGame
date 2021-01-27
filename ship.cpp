#include "stdafx.h"
#include "ship.h"

ship::ship() {}


ship::ship(int _x, int _y)
{
	x = _x;
	y = _y;
}


ship::~ship()
{
}

int ship::getLocationX() {
	return x;
}

int ship::getLocationY() {
	return y;
}





