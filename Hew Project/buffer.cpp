#define _CRT_SECURE_NO_WARNINGS
#include "buffer.h"

CHAR_INFO m_bufScreen[SCREENWIDTH * SCREENHEIGHT];
SMALL_RECT m_rectWindow = { 0,0,128,100 };
CONSOLE_SCREEN_BUFFER_INFOEX consoleSize;
COORD fullScreen = { (short)SCREENWIDTH , (short)SCREENHEIGHT };

//バッファの初期化
void bufferInitialize(void)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(hConsole, TRUE, &m_rectWindow);

	COORD coord = { (short)SCREENWIDTH, (short)SCREENHEIGHT };
	if (!SetConsoleScreenBufferSize(hConsole, coord))
	{
		printf("ErrorSetConsoleScreenBufferSize");
	}

	if (!SetConsoleActiveScreenBuffer(hConsole))
	{
		printf("ErrorSetConsoleActiveScreenBuffer");
	}

	//int fontsize = getSettings();
	int fontsize = 12;

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
	if (!GetConsoleScreenBufferInfo(hConsole, &consoleScreenBufferInfo))
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
	if (!SetConsoleWindowInfo(hConsole, TRUE, &m_rectWindow))
	{
		printf("ErrorSetConsoleWindowInfo");
	}
	//
	if (!SetCurrentConsoleFontEx(hConsole, false, &consoleFontIndex))
	{
		printf("SetCurrentConsoleFontEx");
	}
}

void writePixelToBuffer(int x, int y, int color, int CHAR) {
	(m_bufScreen + (y * SCREENWIDTH) + x)->Attributes = color;
	(m_bufScreen + (y * SCREENWIDTH) + x)->Char.AsciiChar = CHAR;
}

void writeMapToBuffer(int xPos, int yPos, char Map[]) {

	for (int i = yPos; i < SCREENHEIGHT + yPos; i++) {
		for (int j = xPos; j < SCREENWIDTH + xPos; j++) {
			for (int k = 1; k < MAPLAYER; k++) {

				if (colorDecoder(Map[(((i * MAPWIDTH) + j)*MAPLAYER) + k]) != TRANSPARENT) {
					writePixelToBuffer(j - xPos, i - yPos, colorDecoder(Map[(((i * MAPWIDTH) + j)*MAPLAYER) + k]), PIXELFULL);
				}
			}
		}
	}
}

void OutputBuffer() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	WriteConsoleOutput(hConsole, m_bufScreen, fullScreen, { 0,0 }, &m_rectWindow);
}

//void setColor(int col)
//{
//	WORD attr = 0;
//	if (col & INTENSITY)
//		attr |= FOREGROUND_INTENSITY;
//	if (col & RED_MASK)
//		attr |= FOREGROUND_RED;
//	if (col & GREEN_MASK)
//		attr |= FOREGROUND_GREEN;
//	if (col & BLUE_MASK)
//		attr |= FOREGROUND_BLUE;
//	SetConsoleTextAttribute(m_swapped ? m_hCons1 : m_hCons2, attr);
//}
//void setColor(int fg, int bg)
//{
//	WORD attr = 0;
//	if (fg & INTENSITY)
//		attr |= FOREGROUND_INTENSITY;
//	if (fg & RED_MASK)
//		attr |= FOREGROUND_RED;
//	if (fg & GREEN_MASK)
//		attr |= FOREGROUND_GREEN;
//	if (fg & BLUE_MASK)
//		attr |= FOREGROUND_BLUE;
//
//	if (bg & INTENSITY)
//		attr |= BACKGROUND_INTENSITY;
//	if (bg & RED_MASK)
//		attr |= BACKGROUND_RED;
//	if (bg & GREEN_MASK)
//		attr |= BACKGROUND_GREEN;
//	if (bg & BLUE_MASK)
//		attr |= BACKGROUND_BLUE;
//	SetConsoleTextAttribute(m_swapped ? m_hCons1 : m_hCons2, attr);
//}
//void setCursorPos(int x, int y)
//{
//	COORD pos;
//	pos.X = x;
//	pos.Y = y;
//	SetConsoleCursorPosition(m_swapped ? m_hCons1 : m_hCons2, pos);
//}
//void write(const char *ptr)
//{
//	DWORD len = strlen(ptr);
//	WriteConsoleA(m_swapped ? m_hCons1 : m_hCons2, ptr, len, &len, 0);
//}
//void write(const wchar_t *ptr)
//{
//	DWORD len = wcslen(ptr);
//	WriteConsoleW(m_swapped ? m_hCons1 : m_hCons2, ptr, len, &len, 0);
//}
//void write(const std::string &str)
//{
//	DWORD len = str.size();
//	WriteConsoleA(m_swapped ? m_hCons1 : m_hCons2, str.c_str(), len, &len, 0);
//}
//void write(const std::wstring &str)
//{
//	DWORD len = str.size();
//	WriteConsoleA(m_swapped ? m_hCons1 : m_hCons2, str.c_str(), len, &len, 0);
//}
//void swap()
//{
//	if ((m_swapped = !m_swapped)) {
//		SetConsoleActiveScreenBuffer(m_hCons2);
//	}
//	else {
//		SetConsoleActiveScreenBuffer(m_hCons1);
//	}
//}