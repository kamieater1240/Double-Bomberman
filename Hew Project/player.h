#pragma once
#include "main.h"

typedef struct {

	int posX, posY;
	bool isAlive;

}PLAYER;

void InitPlayer(PLAYER* player, COORD pos);
void UpdatePlayer1(PLAYER player1);
void UpdatePlayer2(PLAYER player2);
PLAYER* getPlayer1();
PLAYER* getPlayer2();