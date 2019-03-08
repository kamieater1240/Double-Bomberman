#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "player.h"
#include "bomb.h"

HANDLE hWindow = GetStdHandle(STD_OUTPUT_HANDLE);
int g_nCountFPS;				// FPSカウンタ
int titleMusic, themeMusic, selectSE, takeItemSE, putBombSE, footstepSE, gameoverSE, explosionSE, endMusic;

int main() {

	PLAYER* player1 = getPlayer1();
	PLAYER* player2 = getPlayer2();

	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	int nCountFrame;

	// 分解能を設定
	timeBeginPeriod(1);

	dwExecLastTime = dwFPSLastTime = timeGetTime();
	dwCurrentTime = nCountFrame = 0;

	Initiation();
	standbyScreen();

	playAudio(themeMusic, 1);
	do
	{
		dwCurrentTime = timeGetTime();
		if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 0.5秒ごとに実行
		{
			g_nCountFPS = nCountFrame * 1000 / (dwCurrentTime - dwFPSLastTime);
			dwFPSLastTime = dwCurrentTime;
			nCountFrame = 0;
		}

		if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
		{
			dwExecLastTime = dwCurrentTime;

			Update();

			Draw();

			//#ifdef _DEBUG
			//DispDebug();
			//#endif // DEBUG

			nCountFrame++;
		}
	} while (player1->isAlive && player2->isAlive);

	stopAudio(themeMusic);

	// 分解能を戻す
	timeEndPeriod(1);

	system("cls");

	playAudio(gameoverSE, 1);

	if (player1->isAlive)
		gameOverScreen(1);
	else if (player2->isAlive)
		gameOverScreen(2);

	rewind(stdin);
	getchar();
	stopAudio(gameoverSE);

	playAudio(endMusic, 1);
	thanksForPlaying();

	rewind(stdin);
	getchar();
	return 0;
}

#ifdef _DEBUG
//Debug用表示
void DispDebug(void) {
	gotoxy(1, 1);
	printf("FPS:%d", g_nCountFPS);
}
#endif

//色々ものを初期化する
void Initiation() {
	SetConsoleTitle("DoubleBombs!");
	//SetConsoleDisplayMode(hWindow, CONSOLE_FULLSCREEN_MODE, 0);
	SetConsoleDisplayMode(hWindow, CONSOLE_WINDOWED_MODE, 0);
	cursorSetInvisible();
	readMap();
	readMapTile();
	readObjectTile();
	bufferInitialize();

	InitPlayer(getPlayer1(), { 8, 8 });
	InitPlayer(getPlayer2(), { 120, 72 });
	initBomb();
	initMapEmpty();
	initItem();
	InitMusic();
}

void InitMusic() {
	titleMusic = openAudio("Title.mp3");
	themeMusic = openAudio("Theme.mp3");
	selectSE = openAudio("Select.mp3");
	takeItemSE = openAudio("takeItem.mp3");
	putBombSE = openAudio("putBomb.mp3");
	footstepSE = openAudio("Footstep.mp3");
	gameoverSE = openAudio("gameover.mp3");
	explosionSE = openAudio("explosion.mp3");
	endMusic = openAudio("End.mp3");
}

//各ステータスをアップデートする
void Update() {
	UpdatePlayer1(getPlayer1());
	UpdatePlayer2(getPlayer2());
	UpdateBomb();
}

//画面を描く
void Draw() {

	bufferMap();
	bufferPlayers();
	OutputBuffer();

	Sleep(40);
}