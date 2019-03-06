#pragma once
#include "main.h"

struct Image {
	COORD pos;
	COORD size;
	WORD *color;
};

void loadImage(const char name[], Image* image);
void drawImage(Image image);
WORD getColor(RGBTRIPLE rgb);