#define _CRT_SECURE_NO_WARNINGS
#define CONIOEX
#include "bomb.h"

BOMB bombs[MAX_BOMB];
bool mapEmpty[MAPHEIGHT / 8][MAPWIDTH / 8];

//爆弾を初期化する
void initBomb() {

	for (int i = 0; i < MAX_BOMB; i++) {
		bombs[i].posX = 0;
		bombs[i].posY = 0;
		bombs[i].power = 1;
		bombs[i].explodeCnt = 0;
		bombs[i].isUsed = false;
		bombs[i].fireTimeCnt = 0;
		bombs[i].hasFire = false;
		bombs[i].fromWho = NULL;
		bombs[i].type = BOMBTYPE_NONE;
	}
}

//爆弾をセットする
void setBomb(int posX, int posY, int power, PLAYER* player) {

	for (int i = 0; i < MAX_BOMB; i++) {
		if (!bombs[i].isUsed && !bombs[i].hasFire) {
			bombs[i].posX = posX;
			bombs[i].posY = posY;
			bombs[i].power = power;
			bombs[i].explodeCnt = 0;
			bombs[i].isUsed = true;
			bombs[i].fireTimeCnt = 0;
			bombs[i].hasFire = false;
			bombs[i].fromWho = player;
			bombs[i].type = BOMBTYPE_NORMAL;
			break;
		}
	}
}

//マップ上に爆弾をランダムにセットする
void setRandomBomb(int power) {

	srand(time(NULL));
	int temp, x, y;
	temp = rand() % (186 - 0 + 1) + 0;
	x = temp % 17;
	y = temp / 17;

	while (!checkMapEmpty(x, y)) {
		temp = rand() % (186 - 0 + 1) + 0;
		x = temp % 17;
		y = temp / 17;
	}

	for (int i = 0; i < MAX_BOMB; i++) {
		if (!bombs[i].isUsed && !bombs[i].hasFire) {
			bombs[i].posX = x * 8;
			bombs[i].posY = y * 8;
			bombs[i].power = power;
			bombs[i].explodeCnt = 0;
			bombs[i].isUsed = true;
			bombs[i].fireTimeCnt = 0;
			bombs[i].hasFire = false;
			bombs[i].fromWho = NULL;
			bombs[i].type = BOMBTYPE_ICE;
			break;
		}
	}

	setMapEmpty(x, y, false);
}

//爆弾のステータスをアップデートする
void UpdateBomb() {
	//bombsToMap();
	for (int i = 0; i < MAX_BOMB; i++) {
		if (bombs[i].isUsed) {
			//爆発について
			if (bombs[i].explodeCnt == 45 && bombs[i].hasFire != true) {
				explode(bombs[i]);
				bombs[i].hasFire = true;
				bombs[i].isUsed = false;
				if (bombs[i].fromWho != NULL)
					bombs[i].fromWho->bombPlantedNum--;
			}
			else if (bombs[i].explodeCnt < 45 && bombs[i].hasFire != true) {
				bombs[i].explodeCnt++;
			}

		}
		else {
			if (bombs[i].hasFire) {
				//爆発後の火について
				if (bombs[i].hasFire && bombs[i].fireTimeCnt == 15) {
					bombs[i].hasFire = false;
					clearFires(bombs[i]);
					itemsToMap();
				}
				else if (bombs[i].hasFire && bombs[i].fireTimeCnt < 15) {
					bombs[i].fireTimeCnt++;
					explode(bombs[i]);	//draw one more time, else if two bombs are too close, when clearing the fire of the first bomb, second's fire will be cleared too
				}
			}
		}
	}
}

//爆弾が爆発する時の処理
void explode(BOMB bomb) {
	static char mapReceiveFile[(DECODELAYER * (MAPHEIGHT / 8) * (MAPWIDTH / 8)) + 1];
	strcpy(mapReceiveFile, getMapFileRead());	//基本マップデータをコピー

	//bomb自身のマスのfire
	for (int j = 0; j < DECODELAYER; j++) {
		if (j == 0)
			*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '4';
		else if (j == 1)
			*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '2';
		else if (j == 6)
			*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '6';
		else
			*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '0';
	}

	setMapEmpty(bomb.posX / 8, bomb.posY / 8, true);

	writeMapFileRead(mapReceiveFile);

	if (bomb.type == BOMBTYPE_NORMAL)
		firesToMap(bomb);
	else if (bomb.type == BOMBTYPE_ICE)
		firesToMap(bomb);
}

//爆弾をマップに描く
void bombsToMap() {

	static char mapReceiveFile[(DECODELAYER * (MAPHEIGHT / 8) * (MAPWIDTH / 8)) + 1];
	strcpy(mapReceiveFile, getMapFileRead());	//基本マップデータをコピー

	//爆弾を描く
	for (int i = 0; i < MAX_BOMB; i++) {
		if (bombs[i].isUsed) {
			for (int j = 0; j < DECODELAYER; j++) {
				if (j == 0)
					*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bombs[i].posY / 8)*(MAPWIDTH / 8)) + (bombs[i].posX / 8)) = '3';
				else if (j == 1)
					*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bombs[i].posY / 8)*(MAPWIDTH / 8)) + (bombs[i].posX / 8)) = '2';
				else if (j == 6)
					*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bombs[i].posY / 8)*(MAPWIDTH / 8)) + (bombs[i].posX / 8)) = '5';
				else
					*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bombs[i].posY / 8)*(MAPWIDTH / 8)) + (bombs[i].posX / 8)) = '0';
			}
		}
	}

	writeMapFileRead(mapReceiveFile);
}

//爆弾の火をマップに描く
void firesToMap(BOMB bomb) {
	bool topStop = false, downStop = false, leftStop = false, rightStop = false;
	static char mapReceiveFile[(DECODELAYER * (MAPHEIGHT / 8) * (MAPWIDTH / 8)) + 1];
	strcpy(mapReceiveFile, getMapFileRead());	//基本マップデータをコピー

	srand(time(NULL));

	//爆発範囲の火を描く
	for (int i = 1; i <= bomb.power; i++) {

		//Check bomb up
		if (!topStop) {
			if (*(mapReceiveFile + (((bomb.posY - 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) == '0' || *(mapReceiveFile + (((bomb.posY - 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) == '2'
				|| *(mapReceiveFile + (((bomb.posY - 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) == '5') {
				if (*(mapReceiveFile + (((bomb.posY - 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) == '2') {

					setMapEmpty(bomb.posX / 8, (bomb.posY - 8 * i) / 8, true);

					int createItem = rand() % (100 - 1 + 1) + 1;
					//Create item
					if (createItem < 30) {
						int whichKind = rand() % (100 - 1 + 1) + 1;
						if (whichKind > 50)
							setItem(bomb.posX, bomb.posY - 8 * i, ITEMTYPETYPE_DBBOMB);
						else
							setItem(bomb.posX, bomb.posY - 8 * i, ITEMTYPETYPE_DBPOWER);
					}

					topStop = true;
				}

				for (int j = 0; j < DECODELAYER; j++) {
					if (j == 0)
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY - 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '4';
					else if (j == 1)
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY - 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '2';
					else if (j == 6)
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY - 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '6';
					else
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY - 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '0';
				}
			}
			else
				topStop = true;
		}
		//Check bomb down
		if (!downStop) {
			if (*(mapReceiveFile + (((bomb.posY + 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) == '0' || *(mapReceiveFile + (((bomb.posY + 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) == '2'
				|| *(mapReceiveFile + (((bomb.posY + 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) == '5') {
				if (*(mapReceiveFile + (((bomb.posY + 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) == '2') {

					setMapEmpty(bomb.posX / 8, (bomb.posY + 8 * i) / 8, true);

					int createItem = rand() % (100 - 1 + 1) + 1;
					//Create item
					if (createItem < 30) {
						int whichKind = rand() % (100 - 1 + 1) + 1;
						if (whichKind > 50)
							setItem(bomb.posX, bomb.posY + 8 * i, ITEMTYPETYPE_DBBOMB);
						else
							setItem(bomb.posX, bomb.posY + 8 * i, ITEMTYPETYPE_DBPOWER);
					}

					downStop = true;
				}

				for (int j = 0; j < DECODELAYER; j++) {
					if (j == 0)
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY + 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '4';
					else if (j == 1)
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY + 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '2';
					else if (j == 6)
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY + 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '6';
					else
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY + 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '0';
				}
			}
			else
				downStop = true;
		}
		//Check bomb right
		if (!leftStop) {
			if (*(mapReceiveFile + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX + 8 * i) / 8)) == '0' || *(mapReceiveFile + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX + 8 * i) / 8)) == '2'
				|| *(mapReceiveFile + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX + 8 * i) / 8)) == '5') {
				if (*(mapReceiveFile + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX + 8 * i) / 8)) == '2') {

					setMapEmpty((bomb.posX + 8 * i) / 8, bomb.posY / 8, true);

					int createItem = rand() % (100 - 1 + 1) + 1;
					//Create item
					if (createItem < 30) {
						int whichKind = rand() % (100 - 1 + 1) + 1;
						if (whichKind > 50)
							setItem(bomb.posX + 8 * i, bomb.posY, ITEMTYPETYPE_DBBOMB);
						else
							setItem(bomb.posX + 8 * i, bomb.posY, ITEMTYPETYPE_DBPOWER);
					}

					leftStop = true;
				}

				for (int j = 0; j < DECODELAYER; j++) {
					if (j == 0)
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX + 8 * i) / 8)) = '4';
					else if (j == 1)
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX + 8 * i) / 8)) = '2';
					else if (j == 6)
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX + 8 * i) / 8)) = '6';
					else
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX + 8 * i) / 8)) = '0';
				}
			}
			else
				leftStop = true;
		}
		//Check bomb left
		if (!rightStop) {
			if (*(mapReceiveFile + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX - 8 * i) / 8)) == '0' || *(mapReceiveFile + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX - 8 * i) / 8)) == '2'
				|| *(mapReceiveFile + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX - 8 * i) / 8)) == '5') {
				if (*(mapReceiveFile + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX - 8 * i) / 8)) == '2') {

					setMapEmpty((bomb.posX - 8 * i) / 8, bomb.posY / 8, true);

					int createItem = rand() % (100 - 1 + 1) + 1;
					//Create item
					if (createItem < 30) {
						int whichKind = rand() % (100 - 1 + 1) + 1;
						if (whichKind > 50)
							setItem(bomb.posX - 8 * i, bomb.posY, ITEMTYPETYPE_DBBOMB);
						else
							setItem(bomb.posX - 8 * i, bomb.posY, ITEMTYPETYPE_DBPOWER);
					}

					rightStop = true;
				}

				for (int j = 0; j < DECODELAYER; j++) {
					if (j == 0)
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX - 8 * i) / 8)) = '4';
					else if (j == 1)
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX - 8 * i) / 8)) = '2';
					else if (j == 6)
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX - 8 * i) / 8)) = '6';
					else
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX - 8 * i) / 8)) = '0';
				}
			}
			else
				rightStop = true;
		}
	}

	writeMapFileRead(mapReceiveFile);
}

//爆弾の氷をマップに描く
void iceToMap(BOMB bomb) {

}

//爆弾の火をマップから消す
void clearFires(BOMB bomb) {
	static char mapReceiveFile[(DECODELAYER * (MAPHEIGHT / 8) * (MAPWIDTH / 8)) + 1];
	strcpy(mapReceiveFile, getMapFileRead());	//基本マップデータをコピー

	//爆弾自身のマスの火を消す
	for (int j = 0; j < DECODELAYER; j++) {
		if (j == 1)
			*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bomb.posY / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '2';
		else
			*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bomb.posY / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '0';
	}

	//爆発範囲の火を消す
	for (int i = 1; i <= bomb.power; i++) {

		//Check bomb up
		if (*(mapReceiveFile + (((bomb.posY - 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) == '4') {
			for (int j = 0; j < DECODELAYER; j++) {
				if (j == 1)
					*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY - 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '2';
				else
					*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY - 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '0';
			}
		}
		//Check bomb down
		if (*(mapReceiveFile + (((bomb.posY + 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) == '4') {
			for (int j = 0; j < DECODELAYER; j++) {
				if (j == 1)
					*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY + 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '2';
				else
					*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY + 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '0';
			}
		}
		//Check bomb right
		if (*(mapReceiveFile + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX + 8 * i) / 8)) == '4') {
			for (int j = 0; j < DECODELAYER; j++) {
				if (j == 1)
					*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX + 8 * i) / 8)) = '2';
				else
					*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX + 8 * i) / 8)) = '0';
			}
		}
		//Check bomb left
		if (*(mapReceiveFile + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX - 8 * i) / 8)) == '4') {
			for (int j = 0; j < DECODELAYER; j++) {
				if (j == 1)
					*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX - 8 * i) / 8)) = '2';
				else
					*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX - 8 * i) / 8)) = '0';
			}
		}
	}

	writeMapFileRead(mapReceiveFile);
}

//mapEmptyを初期化する
void initMapEmpty() {

	for (int i = 0; i < MAPHEIGHT / 8; i++) {
		for (int j = 0; j < MAPWIDTH / 8; j++) {
			if (getcharMapFileRead(0, j, i) != '1' && getcharMapFileRead(0, j, i) != '2' && getcharMapFileRead(0, j, i) != '3')
				mapEmpty[i][j] = true;
			else
				mapEmpty[i][j] = false;
		}
	}
}

void setMapEmpty(int posX, int posY, bool value) {
	mapEmpty[posY][posX] = value;
}

bool checkMapEmpty(int posX, int posY) {
	return mapEmpty[posY][posX];
}