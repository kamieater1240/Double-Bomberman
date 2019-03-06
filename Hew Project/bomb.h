#ifndef _BOMB_H_
#define _BOMB_H_

#include "main.h"
#include "player.h"

typedef enum
{
	BOMBTYPE_NONE = 0,
	BOMBTYPE_NORMAL,
	BOMBTYPE_ICE,
}BOMBTYPE;

typedef struct {

	int posX, posY;
	int power;
	int explodeCnt;
	bool isUsed;
	int fireTimeCnt;
	bool hasFire;
	PLAYER* fromWho;
	BOMBTYPE type;

}BOMB;

void initBomb();
void setBomb(int posX, int posY, int power, PLAYER* player);
void setRandomBomb(int power);
void UpdateBomb();
void explode(BOMB);
void bombsToMap();
void firesToMap(BOMB bomb);
void iceToMap(BOMB bomb);
void clearFires(BOMB bomb);
void initMapEmpty();
void setMapEmpty(int posX, int posY, bool value);
bool checkMapEmpty(int posX, int posY);

#endif // !_BOMB_H_