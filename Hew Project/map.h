#pragma once

#include "main.h"

const char * getMapFull(void);
void readMap(void);
void mapDecoder();
int decodeMapCharacters(char encodedCharacter);
void drawMap();

char getcharMapFileRead(int MAP, int LAYER, int X, int Y);
void updateMapFileRead(int ROOM, int DECODE_LAYER, int HEIGHT, int WIDTH, char CHANGE);
int checkBGM(void);
