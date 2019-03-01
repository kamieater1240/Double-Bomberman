#define _CRT_SECURE_NO_WARNINGS
#include "main.h"

HANDLE hWindow = GetStdHandle(STD_OUTPUT_HANDLE);

int main() {

	readMap();
	readMapTile();
	SetConsoleTitle("DoubleBombs!");

	bool endGame = false;
	/*while (!endGame) {

	}*/

	rewind(stdin);
	getchar();
	return 0;
}