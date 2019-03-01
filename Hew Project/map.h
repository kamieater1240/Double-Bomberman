#pragma once

#include "main.h"

const char * getMapFull(void);
void readMap(void);
char getcharMapFileRead(int MAP, int LAYER, int X, int Y);
int decodeMapCharacters(char CHARACTER);
const char * getRawMapFull(void);
void mapDecoder(int ROOM);
void updateMapFileRead(int ROOM, int DECODE_LAYER, int HEIGHT, int WIDTH, char CHANGE);
int checkBGM(void);
