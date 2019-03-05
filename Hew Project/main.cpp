#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "player.h"
#include "bomb.h"

HANDLE hWindow = GetStdHandle(STD_OUTPUT_HANDLE);
int g_nCountFPS;				// FPSカウンタ

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

	// 分解能を戻す
	timeEndPeriod(1);

	system("cls");
	if (!player1->isAlive)
		printf("GameOver!!! Player2 Won!!!");
	else
		printf("GameOver!!! Player1 Won!!!");
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