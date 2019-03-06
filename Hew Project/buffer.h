#pragma once
#include "main.h"

#define SPACE		0x0020

void bufferInitialize(void);
void writePixelToBuffer(int x, int y, int color, int CHAR);
void writeCharInfoToBuffer(int x, int y, CHAR_INFO charInfo);
void writeMapToBuffer(int posX, int posY, char Map[]);
void writePlayerToBuffer(int tileIndex, int posX, int posY, char objectTile[]);
void writeBombToBuffer(int tileIndex, int posX, int posY, char objectTile[]);
void writeTitleBarToBuffer(int posX, int posY, char titleText[]);
void OutputBuffer();
