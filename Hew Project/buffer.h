#pragma once

#include "main.h"

#define PIXELFULL		0x0020

void bufferInitialize(void);
void writePixelToBuffer();
void writeMapToBuffer(int xPos, int yPos, char Map[]);
void OutputBuffer();

//void setColor(int);
//void setColor(int, int);
//void setCursorPos(int, int);
//void write(const char *);
//void write(const wchar_t *);
//void write(const std::string &);
//void write(const std::wstring &);
//void swap();