// ceng241_gameProject.cpp : Defines the entry point for the console application.
//

#pragma once
#include "stdafx.h"

#include <stdlib.h> // for srand() / rand()
#include <stdio.h>
#include "math.h"
#include "ship.h"
#include "mainShip.h"
#include "game.h"

using namespace std;

#define MAPSIZE 32


int main()
{
	game gm (MAPSIZE);
	gm.playGame();

    return 0;
}

