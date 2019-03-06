#pragma once
#include "main.h"

struct Image {
	COORD pos;
	COORD size;
	CHAR_INFO *color;
};

void loadImage(const string & filename, Image& image);
void drawImage(Image image);
void getColor(RGBTRIPLE rgb, CHAR_INFO& charInfo);