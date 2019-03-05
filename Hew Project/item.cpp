#define _CRT_SECURE_NO_WARNINGS
#define CONIOEX
#include "item.h"

ITEM items[MAX_ITEM];

void initItem() {

	for (int i = 0; i < MAX_ITEM; i++) {
		items[i].posX = 0;
		items[i].posY = 0;
		items[i].type = ITEMTYPE_NONE;
		items[i].isUsed = false;
	}
}

void setItem(int posX, int posY, ITEMTYPE type) {

	for (int i = 0; i < MAX_ITEM; i++) {
		if (!items[i].isUsed) {
			items[i].posX = posX;
			items[i].posY = posY;
			items[i].type = type;
			items[i].isUsed = true;
			break;
		}
	}
}

void itemsToMap() {
	static char mapReceiveFile[(DECODELAYER * (MAPHEIGHT / 8) * (MAPWIDTH / 8)) + 1];
	strcpy(mapReceiveFile, getMapFileRead());	//基本マップデータをコピー

	//アイテムをマップデータに入れる
	for (int i = 0; i < MAX_BOMB; i++) {
		if (items[i].isUsed) {
			for (int j = 0; j < DECODELAYER; j++) {
				if (j == 0)
					*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((items[i].posY / 8)*(MAPWIDTH / 8)) + (items[i].posX / 8)) = '5';
				else if (j == 1)
					*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((items[i].posY / 8)*(MAPWIDTH / 8)) + (items[i].posX / 8)) = '2';
				else if (j == 6) {
					if (items[i].type == ITEMTYPETYPE_DBBOMB)
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((items[i].posY / 8)*(MAPWIDTH / 8)) + (items[i].posX / 8)) = '7';
					else
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((items[i].posY / 8)*(MAPWIDTH / 8)) + (items[i].posX / 8)) = '8';
				}
				else
					*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((items[i].posY / 8)*(MAPWIDTH / 8)) + (items[i].posX / 8)) = '0';
			}
		}
	}

	writeMapFileRead(mapReceiveFile);
}

//アイテムをマップから消す
void clearItem(int posX, int posY) {
	static char mapReceiveFile[(DECODELAYER * (MAPHEIGHT / 8) * (MAPWIDTH / 8)) + 1];
	strcpy(mapReceiveFile, getMapFileRead());	//基本マップデータをコピー

	for (int i = 0; i < MAX_ITEM; i++) {
		if (items[i].isUsed) {
			if (items[i].posX == posX && items[i].posY == posY) {


				break;
			}
		}
	}

}