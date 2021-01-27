#pragma once

#include <vector>
#include "ship.h"
#include "mainShip.h"
#include "enemyShip.h"
#include "bullet.h"

using namespace std;
class game
{

private:
	int mapSize;
	vector<enemyShip> enemyShips;
	vector<bullet> bullets;
	mainShip mainSh;
	int shootedEnemies ;
	int missedEnemies;
	bool gameOver;
	
public:
	game(int);
	~game();
	void playGame();
	ship getMainShip();
	ship createEnemyShip(int);
	bullet createBullet();
	void updateShips();
	void updateBullets();
	void checkCollisions();
	void removeMissedShips();
	void drawScene();
	void drawShips();
	void drawBullets();
	void checkEndOfGame();
	void drawFinal();
};

