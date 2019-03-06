#define _CRT_SECURE_NO_WARNINGS
#define CONIOEX
#include "buffer.h"

CHAR_INFO m_bufScreen[SCREENWIDTH * SCREENHEIGHT];
SMALL_RECT m_rectWindow = { 0,0,1,1 };
CONSOLE_SCREEN_BUFFER_INFOEX consoleSize;
COORD fullScreen = { (short)SCREENWIDTH , (short)SCREENHEIGHT };

//バッファの初期化
void bufferInitialize(void)
{
	HANDLE hWindow = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(hWindow, TRUE, &m_rectWindow);

	COORD coord = { (short)SCREENWIDTH, (short)SCREENHEIGHT };
	if (!SetConsoleScreenBufferSize(hWindow, coord))
	{
		printf("ErrorSetConsoleScreenBufferSize");
	}

	if (!SetConsoleActiveScreenBuffer(hWindow))
	{
		printf("ErrorSetConsoleActiveScreenBuffer");
	}

	int fontsize = 8;

	//コンソールのフォントサイズをセットする======================================
	CONSOLE_FONT_INFOEX consoleFontIndex;
	consoleFontIndex.cbSize = sizeof(consoleFontIndex);
	consoleFontIndex.nFont = 0;
	consoleFontIndex.dwFontSize.X = fontsize;
	consoleFontIndex.dwFontSize.Y = fontsize;
	consoleFontIndex.FontFamily = FF_DONTCARE;
	consoleFontIndex.FontWeight = FW_NORMAL;
	//============================================================================

	CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
	if (!GetConsoleScreenBufferInfo(hWindow, &consoleScreenBufferInfo))
	{
		printf("ErrorGetConsoleScreenBufferInfo");
	}
	//
	if (SCREENHEIGHT > consoleScreenBufferInfo.dwMaximumWindowSize.Y)
	{
		printf("ErrorScreenHeight");
	}
	//
	if (SCREENWIDTH > consoleScreenBufferInfo.dwMaximumWindowSize.X)
	{
		printf("ErrorScreenWidth");
	}

	m_rectWindow = { 0, 0, (short)SCREENWIDTH - 1, (short)SCREENHEIGHT - 1 };
	//
	if (!SetConsoleWindowInfo(hWindow, TRUE, &m_rectWindow))
	{
		printf("ErrorSetConsoleWindowInfo");
	}
	//
	if (!SetCurrentConsoleFontEx(hWindow, false, &consoleFontIndex))
	{
		printf("SetCurrentConsoleFontEx");
	}
}

//ピクセルをバッファに描く
void writePixelToBuffer(int x, int y, int color, int CHAR) {
	(m_bufScreen + (y * SCREENWIDTH) + x)->Attributes = color;
	(m_bufScreen + (y * SCREENWIDTH) + x)->Char.AsciiChar = CHAR;
}

//マップをバッファに入れる
void writeMapToBuffer(int xPos, int yPos, char Map[]) {

	for (int i = yPos; i < SCREENHEIGHT + yPos; i++) {
		for (int j = xPos; j < SCREENWIDTH + xPos; j++) {
			for (int k = 1; k < MAPLAYER; k++) {

				if (colorDecoder(Map[(((i * MAPWIDTH) + j) * MAPLAYER) + k]) != TRANSPARENTFLAG) {
					writePixelToBuffer(j - xPos, i - yPos, colorDecoder(Map[(((i * MAPWIDTH) + j) * MAPLAYER) + k]), SPACE);
				}
			}
		}
	}
}

//プレイヤーをバッファに入れる
void writePlayerToBuffer(int tileIndex, int posX, int posY, char objectTile[]) {

	for (int i = 0; i < TILEYSIZE; i++) {
		for (int j = 0; j < TILEXSIZE; j++) {
			if (colorDecoder(objectTile[tileIndex*TILEXSIZE*TILEYSIZE + i * TILEXSIZE + j]) != TRANSPARENTFLAG) {
				writePixelToBuffer(posX + j, posY + i, colorDecoder(objectTile[tileIndex*TILEXSIZE*TILEYSIZE + i * TILEXSIZE + j]), SPACE);
			}
		}
	}
}

//爆弾をバッファに入れる
void writeBombToBuffer(int tileIndex, int posX, int posY, char objectTile[]) {

	for (int i = 0; i < TILEYSIZE; i++) {
		for (int j = 0; j < TILEXSIZE; j++) {
			if (colorDecoder(objectTile[tileIndex*TILEXSIZE*TILEYSIZE + i * TILEXSIZE + j]) != TRANSPARENTFLAG) {
				writePixelToBuffer(posX + j, posY + i, colorDecoder(objectTile[tileIndex*TILEXSIZE*TILEYSIZE + i * TILEXSIZE + j]), SPACE);
			}
		}
	}
}

//titleTextをバッファに入れる
void writeTitleBarToBuffer(int posX, int posY, char titleText[]) {

	for (int i = 0; i < strlen(titleText); i++) {
		writePixelToBuffer(posX + i, posY, colorDecoder(titleText[i]), SPACE);
	}
}

//バッファを出力する
void OutputBuffer() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	WriteConsoleOutput(hConsole, m_bufScreen, fullScreen, { 0,0 }, &m_rectWindow);
}
