#pragma once

#include "main.h"

const char * getMapFull(void);
void readMap(void);
void mapDecoder();
int decodeMapCharacters(char encodedCharacter);
void bufferMap();
char getcharMapFileRead(int layer, int playerX, int playerY);
void updateMapFileRead(int ROOM, int DECODE_LAYER, int HEIGHT, int WIDTH, char CHANGE);
int checkBGM(void);
