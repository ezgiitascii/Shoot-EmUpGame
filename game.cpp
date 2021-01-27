#pragma once

#include "stdafx.h"
#include <time.h>
#include <vector>
#include "game.h"
#include "ship.h"
#include "mainShip.h"
#include "enemyShip.h"
#include <stdlib.h> // for srand() / rand()
#include "rlutil.h"
#include <cmath>


#define SCREENTIME 40000

using namespace rlutil;
using namespace std;

game::game(int _mapSize)
{
	mapSize = _mapSize;
	mainShip ms (mapSize / 2, mapSize);
	mainSh = ms;
	shootedEnemies = 0;
	missedEnemies = 0;
	gameOver = false;
}


game::~game()
{
}

ship game::getMainShip() {
	return mainSh;
}

ship game::createEnemyShip(int mapSize) {
	srand(time(NULL));
	enemyShip ts(rand() % mapSize, 5);
	enemyShips.push_back(ts);
	return ts;
}

bullet game::createBullet() {
	srand(time(NULL));
	bullet b(mainSh.getLocationX(), mainSh.getLocationY());
	bullets.push_back(b);
	return b;
}

void game::updateShips() {
	vector<enemyShip>::iterator it;
	int i = 0;
	for (it = enemyShips.begin(); it != enemyShips.end(); it++, i++) {
		if(!enemyShips.at(i).isShooted())
			enemyShips.at(i).moveDown();
	}
}


void game::updateBullets() {
	vector<bullet>::iterator itb;
	int i = 0;
	for (itb = bullets.begin(); itb != bullets.end(); itb++, i++) {
		bullets.at(i).moveUp();
	}
}

void game::checkCollisions() {
	vector<enemyShip>::iterator it;
	vector<bullet>::iterator itb;
	int i = 0, j = 0;
	for (it = enemyShips.begin(); it != enemyShips.end(); it++, i++) {
		for (itb = bullets.begin(); itb != bullets.end(); itb++, j++) {
			if (abs(enemyShips.at(i).getLocationX() - bullets.at(j).getLocationX()) <= 1 &&
				abs(enemyShips.at(i).getLocationY() - bullets.at(j).getLocationY()) <= 1) {
				enemyShips.at(i).destroyShip();
				bullets.at(j).destroyBullet();
			}

		}
		j = 0;
	}
}

void game::checkEndOfGame() {
	vector<enemyShip>::iterator it;
	int i = 0; 
	for (it = enemyShips.begin(); it != enemyShips.end(); it++, i++) {
		if (enemyShips.at(i).getLocationX() == mainSh.getLocationX() &&
			enemyShips.at(i).getLocationY() == mainSh.getLocationY())
		{
			gameOver = true;
		}
	}
	

}

void game::removeMissedShips() {
	vector<enemyShip>::iterator it;
	int i = 0;
	for (it = enemyShips.begin(); it != enemyShips.end(); it++, i++) {
		if (enemyShips.at(i).getLocationY() >= mapSize) {
			enemyShips.at(i).missedShip();
		}
	}
}

void game::drawScene() {
	cls();
	setColor(RED);
	for (int i = 1; i < mapSize; i++)
	{
		locate(1, i);
		printf("|");
		locate(mapSize, i);
		printf("|");
		locate(i, 1);
		printf("'");
		locate(i, mapSize);
		printf("--");
	}

	int i = 0;
	vector<enemyShip>::iterator it;
	shootedEnemies = 0;
	for (it = enemyShips.begin(); it != enemyShips.end(); it++, i++) {
		if (enemyShips.at(i).isShooted())
			shootedEnemies++;
	}
	locate(40, 5);
	setColor(MAGENTA);
	printf("\\v/ Shooted : %d", shootedEnemies);

	i = 0;
	missedEnemies = 0;
	for (it = enemyShips.begin(); it != enemyShips.end(); it++, i++) {
		if (enemyShips.at(i).isMissed())
			missedEnemies++;
	}
	locate(40, 10);
	setColor(RED);
	printf("\\v/ Missed : %d", missedEnemies);

	locate(1, mapSize + 3);
	setColor(YELLOW);
	fflush(stdout);
}

void game::drawShips() {

	vector<enemyShip>::iterator it;
	int i = 0;
	for (it = enemyShips.begin(); it != enemyShips.end(); it++, i++) {
		if (!enemyShips.at(i).isShooted() && !enemyShips.at(i).isMissed()) {
			locate(enemyShips.at(i).getLocationX(), enemyShips.at(i).getLocationY());
			setColor(GREY);
			printf("\\v/");
		}
	}

	locate(mainSh.getLocationX(), mainSh.getLocationY());
	setColor(GREEN);
	printf("/^\\");
}

void game::drawBullets() {

	vector<bullet>::iterator it;
	int i = 0;
	for (it = bullets.begin(); it != bullets.end(); it++, i++) {
		if (!bullets.at(i).isShooted()) {
			locate(bullets.at(i).getLocationX(), bullets.at(i).getLocationY());
			setColor(RED);
			printf("'");
		}
	}
}
void game::drawFinal() {
	cls();
	locate(mapSize / 2, mapSize / 2);
	setColor(GREEN);
	printf("GAME OVER :) ");
	locate(mapSize / 2, (mapSize / 2)-3);
	setColor(BLUE);
	printf("You shooted x");
	gameOver = true;

}
void game::playGame() {
	hidecursor();
	saveDefaultColor();
	setColor(2);
	printf("Welcome! Use Left and Right Arrows to move and Up Key to fire, ESC to quit.\n");
	setColor(6);
	anykey("Hit any key to start.\n");
	drawScene();
	drawShips();
	
	int enemyTimer = 0;
	int screenTimer = 0;

	while (1) {
		if (gameOver) {
			break;
		}
		enemyTimer++;
		screenTimer++;
		// Input
		if (kbhit()) {
			char k = getkey();
			
			if (k == KEY_ESCAPE) {
				break;
			}
			else if (k == KEY_LEFT && mainSh.getLocationX() > 1)
			{
				mainSh.moveLeft();
			}
			else if (k == KEY_RIGHT && mainSh.getLocationX() < mapSize - 1)
			{
				mainSh.moveRight();
			}
			else if (k == KEY_UP)
			{
				createBullet();
			}
			

		}

		if ((enemyTimer % (SCREENTIME * 2)) == 0) {
			enemyTimer = 0;
			createEnemyShip(mapSize);
		}

		if ((screenTimer % SCREENTIME) == 0) {
			updateShips();
		}

		if ((screenTimer % (SCREENTIME/10)) == 0) {
			updateBullets();
			checkCollisions();
			removeMissedShips();
			drawScene();
			drawShips();
			drawBullets();
			checkEndOfGame();
		}


	}
	drawFinal();
	anykey("Hit any key to stop.\n");
	cls();
	resetColor();
	showcursor();

}