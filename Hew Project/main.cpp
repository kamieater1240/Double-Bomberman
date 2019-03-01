#define _CRT_SECURE_NO_WARNINGS
#include "main.h"

HANDLE hWindow = GetStdHandle(STD_OUTPUT_HANDLE);

void Initiation() {
	bufferInitialize();
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	cursorSetInvisible();
	readMap();
	readMapTile();
	SetConsoleTitle("DoubleBombs!");
}

int main() {

	Initiation();

	bool endGame = false;
	/*while (!endGame) {

	}*/
	drawMap();
	printf("");

	rewind(stdin);
	getchar();
	return 0;
}