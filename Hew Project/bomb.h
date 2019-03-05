#ifndef _BOMB_H_
#define _BOMB_H_

#include "main.h"
#include "player.h"

typedef struct {

	int posX, posY;
	int power;
	int explodeCnt;
	bool isUsed;
	int fireTimeCnt;
	bool hasFire;
	PLAYER* fromWho;

}BOMB;

void initBomb();
void setBomb(int posX, int posY, int power, PLAYER* player);
void UpdateBomb();
void explode(BOMB);
void bombsToMap();
void firesToMap(BOMB bomb);
void clearFires(BOMB bomb);

#endif // !_BOMB_H_