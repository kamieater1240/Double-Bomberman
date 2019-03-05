#pragma once
#include "main.h"

typedef enum
{
	ITEMTYPE_NONE = 0,
	ITEMTYPETYPE_DBBOMB,
	ITEMTYPETYPE_DBPOWER,
}ITEMTYPE;

typedef struct {
	int posX, posY;
	ITEMTYPE type;
	bool isUsed;
}ITEM;

void initItem();
void setItem(int posX, int posY, ITEMTYPE type);
void itemsToMap();
void clearItem(int posX, int posY);