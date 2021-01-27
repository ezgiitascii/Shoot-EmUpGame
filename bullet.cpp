#include "stdafx.h"
#include <stdlib.h> // for srand() / rand()
#include <stdio.h>
#include "math.h"
#include "bullet.h"


bullet::bullet()
{
}


bullet::~bullet()
{
}

bullet::bullet(int _x, int _y)
{
	x = _x;
	y = _y;
	shooted = false;
}
void bullet::moveUp() {
	y = y - 1;
}
int bullet::getLocationX() {
	return x;
}

int bullet::getLocationY() {
	return y;
}

void bullet::destroyBullet() {
	shooted = true;
}

bool bullet::isShooted() {
	return shooted;
}