#define _CRT_SECURE_NO_WARNINGS
#define CONIOEX
#include "startandend.h"
#include "image.h"

void standbyScreen() {

	Image title1, title2;

	loadImage("BomberMan1", &title1);
	loadImage("BomberMan2", &title2);

	/*ifstream loadtitle;
	loadtitle.open("gameover.txt");
	char titleText[31][134];
	string tmp;
	int row = 0;

	while (!loadtitle.eof()) {
		getline(loadtitle, tmp);
		for (int i = 0; i < tmp.length(); i++) {
			titleText[row][i] = tmp[i];
		}
		titleText[row][tmp.length()] = '\0';

		writeTitleBarToBuffer(2, 2 + row, titleText[row]);
		row++;
	}*/

	rewind(stdin);

	while (!kbhit()) {
		
		drawImage(title1);
		Sleep(1000);
		drawImage(title2);
		Sleep(1000);
	}
}


void gameOverScreen(int winner) {

	ifstream load, ldWin;
	load.open("gameover.txt");
	char gameOverText[31][134];
	char winText[31][89];
	string tmp;
	int row = 0;

	if (winner == 1)
		ldWin.open("P1win.txt");
	else if (winner == 2)
		ldWin.open("P2win.txt");

	while (!load.eof()) {
		getline(load, tmp);
		for (int i = 0; i < tmp.length(); i++) {
			gameOverText[row][i] = tmp[i];
		}
		gameOverText[row][tmp.length()] = '\0';

		writeTitleBarToBuffer(2, 2 + row, gameOverText[row]);
		row++;
	}

	row = 0;
	while (!ldWin.eof()) {
		getline(ldWin, tmp);
		for (int i = 0; i < tmp.length(); i++) {
			winText[row][i] = tmp[i];
		}
		winText[row][tmp.length()] = '\0';

		writeTitleBarToBuffer(2, 50 + row, winText[row]);
		row++;
	}

	OutputBuffer();
}