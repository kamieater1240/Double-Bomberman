#ifndef _BOMB_H_
#define _BOMB_H_

#include "main.h"

typedef struct {

	int posX, posY;
	int power;
	int explodeCnt;
	bool isUsed;
	PLAYER* fromWho;

}BOMB;

void initBomb();
void setBomb(int posX, int posY, int power, PLAYER* player);
void UpdateBomb();
void explode();
void bufferBombs();
void bufferFires();

#endif // !_BOMB_H_