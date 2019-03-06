#define _CRT_SECURE_NO_WARNINGS
#define CONIOEX
#include "image.h"

void loadImage(const char name[], Image* image) {
	FILE *file;
	char path[_MAX_PATH] = "Resources/";
	char ext[_MAX_EXT] = ".bmp";
	BITMAPFILEHEADER bmpFile;
	BITMAPINFOHEADER bmpInfo;
	int colorSize;
	RGBTRIPLE *bmpColor;

	strcat_s(path, name);
	strcat_s(path, ext);
	fopen_s(&file, path, "rb");
	fread((char*)&bmpFile, sizeof(BITMAPFILEHEADER), 1, file);
	fread((char*)&bmpInfo, sizeof(BITMAPINFOHEADER), 1, file);

	colorSize = sizeof(RGBTRIPLE) * bmpInfo.biWidth * bmpInfo.biHeight;
	bmpColor = (RGBTRIPLE*)malloc(colorSize);
	fread((char*)bmpColor, colorSize, 1, file);

	// âÊëúÇÃêFÇì«Ç›çûÇﬁ
	for (int row = 0; row < bmpInfo.biHeight; row++) {
		for (int col = 0; col < bmpInfo.biWidth; col++) {
			image->color[row * image->size.X + col] = getColor(bmpColor[(bmpInfo.biHeight - 1 - row) * bmpInfo.biWidth + col]);
		}
	}

	free(bmpColor);
	fclose(file);
}

void drawImage(Image image) {

	for (int i = 0; i < image.size.Y; i++) {
		for (int j = 0; j < image.size.X; j++) {
			writePixelToBuffer(j, i, colorDecoder(image.color[i * image.size.X + j]), SPACE);
		}
	}

	OutputBuffer();
}

WORD getColor(RGBTRIPLE rgb) {
	// RGBÇWORDÇ…ïœä∑Ç∑ÇÈ
	if (rgb.rgbtRed == rgb.rgbtGreen && rgb.rgbtGreen == rgb.rgbtBlue) {
		switch (rgb.rgbtRed) {
		case 0:
			return BLACK;
		case 128:
			return DARK_GRAY;
		case 192:
			return LIGHT_GRAY;
		case 255:
			return WHITE;
		}
	}
	else if (rgb.rgbtRed == rgb.rgbtGreen) {
		switch (rgb.rgbtRed) {
		case 0:
			return rgb.rgbtBlue == 255 ? BLUE : DARK_BLUE;
		case 128:
			return DARK_YELLOW;
		case 255:
			return YELLOW;
		}
	}
	else if (rgb.rgbtGreen == rgb.rgbtBlue) {
		switch (rgb.rgbtGreen) {
		case 0:
			return rgb.rgbtRed == 255 ? RED : DARK_RED;
		case 128:
			return DARK_CYAN;
		case 255:
			return CYAN;
		}
	}
	else if (rgb.rgbtBlue == rgb.rgbtRed) {
		switch (rgb.rgbtBlue) {
		case 0:
			return rgb.rgbtGreen == 255 ? GREEN : DARK_GREEN;
		case 128:
			return DARK_VIOLET;
		case 255:
			return VIOLET;
		}
	}
	return BLACK;
}