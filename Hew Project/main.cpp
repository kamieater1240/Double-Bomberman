#define _CRT_SECURE_NO_WARNINGS
#include "main.h"

HANDLE hWindow = GetStdHandle(STD_OUTPUT_HANDLE);
int g_nCountFPS;				// FPS�J�E���^

int main() {


	bool endGame = false;
	//drawMap();

	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	int nCountFrame;

	// ����\��ݒ�
	timeBeginPeriod(1);

	dwExecLastTime = dwFPSLastTime = timeGetTime();
	dwCurrentTime = nCountFrame = 0;

	Initiation();

	do
	{
		dwCurrentTime = timeGetTime();
		if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 0.5�b���ƂɎ��s
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
	} while (!inport(PK_ESC));

	// ����\��߂�
	timeEndPeriod(1);

	rewind(stdin);
	getchar();
	return 0;
}

#ifdef _DEBUG
//Debug�p�\��
void DispDebug(void) {
	gotoxy(1, 1);
	printf("FPS:%d", g_nCountFPS);
}
#endif

//�F�X���̂�����������
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

//�e�X�e�[�^�X���A�b�v�f�[�g����
void Update() {
	UpdatePlayer1(getPlayer1());
	UpdatePlayer2(getPlayer2());
	UpdateBomb();
}

//��ʂ�`��
void Draw() {

	bufferMap();
	bufferBombs();
	bufferPlayers();
	OutputBuffer();

	Sleep(40);
}