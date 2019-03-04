#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

typedef struct {

	int posX, posY;
	bool isAlive;
	int canPlantBombNum, bombPlantedNum;
	int bombPower;

}PLAYER;

void InitPlayer(PLAYER* player, COORD pos);
void UpdatePlayer1(PLAYER* player1);
void UpdatePlayer2(PLAYER* player2);
void bufferPlayers();
PLAYER* getPlayer1();
PLAYER* getPlayer2();

#endif // !_PLAYER_H_