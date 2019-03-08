#define _CRT_SECURE_NO_WARNINGS
#define CONIOEX
#include "image.h"

void loadImage(const string & filename, Image& image) {
	
	// file path
	string path{ "Resources\\" };
	path = path + filename + ".bmp";
	//open the bmp file
	fstream fs(path, ios::binary | ios::in);
	//if fail return -1
	if (!fs)
	{
		return;
	}
	//file header
	BITMAPFILEHEADER bmpFile;
	BITMAPINFOHEADER bmpInfo;
	//read file header
	fs.read(reinterpret_cast<char*>(&bmpFile), sizeof BITMAPFILEHEADER);
	//if not bmp file return -1
	if (bmpFile.bfType != 'MB')
	{
		return;
	}
	//red bmp info header
	fs.read(reinterpret_cast<char*>(&bmpInfo), sizeof BITMAPINFOHEADER);

	int pixelNum = bmpInfo.biWidth * bmpInfo.biHeight;
	RGBTRIPLE *bmpColor = new RGBTRIPLE[pixelNum];
	fs.read(reinterpret_cast<char*>(bmpColor), sizeof(RGBTRIPLE) * pixelNum);

	//save bmp size
	image.size.X = bmpInfo.biHeight;
	image.size.Y = bmpInfo.biWidth;

	image.color = new CHAR_INFO[pixelNum];

	// âÊëúÇÃêFÇì«Ç›çûÇﬁ
	for (int i = 0; i < pixelNum; i++) {
		//getColor(bmpColor[i], *(image.color + i));
		getColor(*(bmpColor + i), *(image.color + i));
	}

}

void drawImage(Image image) {

	for (int i = 0; i < image.size.X; i++) {
		for (int j = 0; j < image.size.Y; j++) {
			writeCharInfoToBuffer(j, i, *(image.color + (image.size.X - 1 - i) * image.size.Y + j));
		}
	}

	OutputBuffer();
}

void getColor(RGBTRIPLE rgb, CHAR_INFO& charInfo) {

	charInfo.Attributes = 0x00;
	charInfo.Char.UnicodeChar = ' ';

	if (rgb.rgbtRed == 0x00)
	{
		if (rgb.rgbtGreen == rgb.rgbtBlue && rgb.rgbtGreen == 0x00)
		{
			return;
		}
		else
		{
			charInfo.Attributes = 0x0f;
			charInfo.Char.UnicodeChar = (rgb.rgbtGreen << 8) + rgb.rgbtBlue;
		}
	}
	else
	{
		int colorSum = rgb.rgbtBlue + rgb.rgbtGreen + rgb.rgbtRed;
		short tmp = 0x00;
		if (rgb.rgbtBlue >> 7 == 1)
		{
			tmp++;
		}
		if (rgb.rgbtGreen >> 7 == 1)
		{
			tmp += 0x2;
		}
		if (rgb.rgbtRed >> 7 == 1)
		{
			tmp += 0x4;
		}
		if (colorSum > 128 * 3)
		{
			tmp += 0x8;
		}
		charInfo.Attributes = tmp << 4;;
	}
	return;
}