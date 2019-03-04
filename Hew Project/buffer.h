#pragma once
#include "main.h"

#define PIXELFULL		0x0020

void bufferInitialize(void);
void writePixelToBuffer(int x, int y, int color, int CHAR);
void writeMapToBuffer(int posX, int posY, char Map[]);
void writePlayerToBuffer(int tileIndex, int posX, int posY, char objectTile[]);
void writeBombToBuffer(int tileIndex, int posX, int posY, char objectTile[]);
//void writeFireToBuffer(int tileIndex, int posX, int posY, char objectTile[], BOMB explodedBomb);
void OutputBuffer();
