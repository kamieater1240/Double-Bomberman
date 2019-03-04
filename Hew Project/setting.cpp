#define _CRT_SECURE_NO_WARNINGS
#define CONIOEX
#include "setting.h"

//ÉJÅ[É\ÉãÇâBÇ∑
void cursorSetInvisible(void)
{
	CONSOLE_CURSOR_INFO info;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &info);
}