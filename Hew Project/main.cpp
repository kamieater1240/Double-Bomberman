#define _CRT_SECURE_NO_WARNINGS
#include "main.h"

HANDLE hWindow = GetStdHandle(STD_OUTPUT_HANDLE);

void Initiation() {
	SetConsoleTitle("DoubleBombs!");
	//SetConsoleDisplayMode(hWindow, CONSOLE_FULLSCREEN_MODE, 0);
	cursorSetInvisible();
	readMap();
	readMapTile();
	readObjectTile();
	bufferInitialize();
}

int main() {

	Initiation();

	bool endGame = false;
	/*while (!endGame) {

	}*/
	drawMap();

	rewind(stdin);
	getchar();
	return 0;
}